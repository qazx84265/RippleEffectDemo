//
//  RippleView.m
//  RippleEffect
//
//  Created by 123 on 15/9/14.
//  Copyright (c) 2015年 com.pureLake. All rights reserved.
//

#import "RippleView.h"



#define SCREEN_WIDTH CGRectGetWidth([UIScreen mainScreen].bounds)
#define SCREEN_HEIGHT CGRectGetHeight([UIScreen mainScreen].bounds)



#define BITS_PER_COMPONENT 8
#define BYTES_PER_PIXEL 4




#define COLOR_SPACE CGColorSpaceCreateDeviceRGB()





@interface RippleView() {
    size_t width;
    size_t height;
    
    size_t imageWidth;
    size_t imageHeight;
    
    size_t frameWidth;
    size_t frameHeight;
    
    short *currentWaveBuff;
    short *nextWaveBuff;
    
    int *source;
    int *dest;
    
    
    
    bool isRaining;
}
@property (nonatomic, strong) UIImage *image;
@property (nonatomic, assign) CGImageRef imageRef;
@property (nonatomic, assign) CGRect drawRect;
@end

@implementation RippleView

- (instancetype)init {
    return [self initWithFrame:CGRectMake(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)];
}


- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        isRaining = true;
//        self.backgroundColor = [UIColor whiteColor];
        width = frame.size.width;
        height = frame.size.height;
        
        
        
        
        //load image
        self.image = [UIImage imageNamed:@"water.jpg"];
        self.imageRef = self.image.CGImage;
        
        imageWidth = CGImageGetWidth(self.imageRef);
        imageHeight = CGImageGetHeight(self.imageRef);
        width = imageWidth;
        height = imageHeight;
        
        //init buff
        currentWaveBuff = malloc(width*height*sizeof(short));
        memset(currentWaveBuff, 0, width*height*sizeof(short));
        
        nextWaveBuff = malloc(width*height*sizeof(short));
        memset(nextWaveBuff, 0, width*height*sizeof(short));
        
        //读取原图像素数据
        size_t bytesPerRow = imageWidth * BYTES_PER_PIXEL;
        size_t bytesTotal = bytesPerRow * imageHeight;
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
//        void *bitmap = malloc(bytesTotal);
        CGContextRef context = CGBitmapContextCreate(nil, imageWidth, imageHeight, BITS_PER_COMPONENT, bytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast|kCGBitmapByteOrder32Big);
        CGContextDrawImage(context, CGRectMake(0, 0, imageWidth, imageHeight), self.imageRef);
        source = CGBitmapContextGetData(context);
        CGColorSpaceRelease(colorSpace);
        
        dest = malloc(bytesTotal);
        memcpy(dest, source, bytesTotal);
        
        
//        for (int i=0; i<imageWidth; ++i) {
//            for (int j=0; j<imageHeight; ++j) {
//                if (j != 0) {
//                    printf(" ");
//                }
//                printf("%d",*(dest+(i*imageWidth+j)));
//            }
//            printf("\r\r");
//        }
        
        
        //draw rect
        frameWidth = frame.size.width;
        frameHeight = frame.size.height;
        self.drawRect = CGRectZero;
        if (imageWidth <= frameWidth && imageHeight <= frameHeight) {
            self.drawRect = CGRectMake(0, 0, imageWidth, imageHeight);
        } else {
            //缩放
            CGFloat scale = 0.0;
            if (imageWidth > frameWidth && imageHeight <= frameHeight) {
                scale = (CGFloat)imageWidth / frameWidth;
            } else if (imageWidth <= frameWidth && imageHeight > frameHeight) {
                scale = (CGFloat)imageHeight / frameHeight;
            } else {
                if (imageWidth <= imageHeight) {
                    scale = (CGFloat)imageHeight / frameHeight;
                } else {
                    scale = (CGFloat)imageWidth / frameWidth;
                }
            }
            
            NSLog(@"scale:%f",scale);
            self.drawRect = CGRectMake(0, (frameHeight- (imageHeight / scale))/2/*垂直居中*/, imageWidth / scale, imageHeight / scale);
        }
    }
    
    
    return self;
}







- (void)drawRect:(CGRect)rect {
//    //获取绘图上下文
//    CGContextRef ctx = UIGraphicsGetCurrentContext();
//    
//    //翻转
//    CGContextScaleCTM(ctx, 1.0, -1.0);
//    CGContextTranslateCTM(ctx, 0, height);//向上平移
//
//    //绘图
//    CGContextDrawImage(ctx, self.bounds, self.imageRef);
//    
//    //释放
//    CGContextRelease(ctx);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CFDataRef cfData = CFDataCreate(NULL, (unsigned char*)dest, (imageWidth*BYTES_PER_PIXEL)*imageHeight);
    CGDataProviderRef provider = CGDataProviderCreateWithCFData(cfData);
    CGImageRef imageRef = CGImageCreate(imageWidth, imageHeight, BITS_PER_COMPONENT, BYTES_PER_PIXEL*BITS_PER_COMPONENT, imageWidth*BYTES_PER_PIXEL, colorSpace, kCGImageAlphaPremultipliedLast|kCGBitmapByteOrder32Big, provider, nil, false, kCGRenderingIntentDefault);
    UIImage *image = [UIImage imageWithCGImage:imageRef];
    [image drawInRect:self.drawRect];
    image = nil;
    
    //release
    CFRelease(cfData);
    CFRelease(provider);
    CGImageRelease(imageRef);
    CGColorSpaceRelease(colorSpace);
}



//MARK:--water effect

/**
 水波传播
 // 某点下一时刻的波幅算法为：上下左右四点的波幅和的一半减去当前波幅，即
 // 		X0' =（X1 + X2 + X3 + X4）/ 2 - X0
 //  +----x3----+
 //  +    |     +
 //  +    |     +
 //	x1---x0----x2
 //  +    |     +
 //  +    |     +
 //  +----x4----+
 //
 */
- (void)rippleSpread {
    size_t pixels = width * (height - 1);
    for (size_t i = width; i < pixels; ++i) {
        // 波能扩散:下一时刻某点振幅 = 上下左右四点的波幅和的一半减去当前波幅
        // X0' =（X1 + X2 + X3 + X4）/ 2 - X0
        //
        *(nextWaveBuff+i) = ((*(currentWaveBuff+i-1) + *(currentWaveBuff+i+1) + *(currentWaveBuff+i-width) + *(currentWaveBuff+i+width)) >> 1) - *(nextWaveBuff+i);
        
        // 振幅衰减 1/32
        *(nextWaveBuff+i) -= *(nextWaveBuff+i) >> 5;
    }
    
    //交换振幅数据缓冲区
//    short *temp = malloc(width * height);
//    memcpy(temp, currentWaveBuff, width * height);
    short *temp = currentWaveBuff;
    currentWaveBuff = nextWaveBuff;
    nextWaveBuff = temp;
//    free(temp);
    temp = NULL;
}



/**
 水波渲染
 */
- (void)rippleRender {
    size_t offset;
    size_t i = width;
    size_t length = width * height;
    
    for (int y=1; y<height-1; ++y) {
        for (int x=0; x<width; ++x, ++i) {
            //计算出偏移像素与原始像素的内存地址偏移量 offset = width * yoffset + xoffset
            offset = (width * (*(currentWaveBuff+i-width)-*(currentWaveBuff+i+width))) + (*(currentWaveBuff+i-1) - *(currentWaveBuff+i+1));
            
            //判断坐标是否在窗口范围内
            if (i+offset > 0 && i+offset<length) {
                *(dest+i) = *(source+i+offset);
            } else {
                *(dest+i) = *(source+i);
            }
        }
    }
}


/**
 生成一个水波
 // 为了形成水波，我们必须在水池中加入波源，你可以想象成向水中投入石头，
 // 形成的波源的大小和能量与石头的半径和扔石头的力量都有关系。
 // 我们只要修改波能数据缓冲区 buf，让它在石头入水的地点来一个负的"尖脉冲"，
 // 即让  buf[x, y] = -n。经过实验，n 的范围在（32 ~ 128）之间比较合适。
 // stoneSize 	: 波源半径
 // stoneWeight 	: 波源能量
 //
 :param: x
 :param: y
 :param: stoneSize
 :param: stoneWeight
 */
- (void)dropStoneAtX:(int)x Y:(int)y withSize:(int)size andWeight:(int)weight {
    //判断坐标是否在窗口范围内
    if (x+size>width || y+size>height || x-size<0 || y-size<0) {
        return;
    }
    
    int value = size * size;
    int wgt = (short)-weight;
    
    for (int posx=x-size; posx<x+size; ++posx) {
        for (int posy=y-size; posy<y+size; ++posy) {
            if (((posx-x) * (posx-x) + (posy-y) * (posy-y)) < value) {
                *(currentWaveBuff+width*posy+posx) = wgt;
            }
        }
    }
}


- (void)dropStoneLineAtX:(int)x Y:(int)y withSize:(int)size andWeight:(int)weight {
    //判断坐标是否在窗口范围内
    if (x+size>width || y+size>height || x-size<0 || y-size<0) {
        return;
    }
    
    for (int posx=x-size; posx<x+size; ++posx) {
        for (int posy=y-size; posy<y+size; ++posy) {
            *(currentWaveBuff+width+posx+posy) = -40;
        }
    }
}


/**
 滑动生成一条水波
 
 :param: sx
 :param: sy
 :param: ex
 :param: ey
 :param: size
 :param: weight
 */
- (void)bresenhamDropSX:(int)sx SY:(int)sy EX:(int)ex EY:(int)ey withSize:(int)size andWeight:(int)weight {
    int startX = sx;
    int startY = sy;
    int endX = ex;
    int endY = ey;
    
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    
    if (dx == 0 && dy == 0) {
        [self dropStoneLineAtX:startX Y:startY withSize:size andWeight:weight];
    } else if (dx == 0) {
        int yinc = (ey-sy != 0) ? 1 : -1;
        for (int i=0; i<dy; ++i) {
            [self dropStoneLineAtX:startX Y:startY withSize:size andWeight:weight];
            startY += yinc;
        }
    } else if (dy == 0) {
        int xinc = (ex-sx != 0) ? 1 : -1;
        for (int i=0; i<dx; ++i) {
            [self dropStoneLineAtX:startX Y:startY withSize:size andWeight:weight];
            startY += xinc;
        }
    } else if (dx > dy) {
        int p = (dy << 1) - dx;
        int inc1 = dy << 1;
        int inc2 = (dy - dx) << 1;
        int xinc = (endX - startX != 0) ? 1 : -1;
        int yinc = (endY - startY != 0) ? 1 : -1;
        
        for (int i=0; i<dx; ++i) {
            [self dropStoneLineAtX:startX Y:startY withSize:size andWeight:weight];
            startX += xinc;
            if (p < 0) {
                p += inc1;
            } else {
                startY += yinc;
                p += inc2;
            }
        }
    } else {
        int p = (dx << 1) - dy;
        int inc1 = dx << 1;
        int inc2 = (dx - dy) << 1;
        int xinc = (endX - startX != 0) ? 1 : -1;
        int yinc = (endY - startY != 0) ? 1 : -1;
        
        for (int i=0; i<dy; ++i) {
            [self dropStoneLineAtX:startX Y:startY withSize:size andWeight:weight];
            startY += yinc;
            if (p < 0) {
                p += inc1;
            } else {
                startX += xinc;
                p += inc2;
            }
        }
    }
}






/**
 *  模拟雨滴
 */
- (void)raining {
    if (isRaining) {
        srand((unsigned)time(0));
        int x = 10 + (rand() % (width-20));
        int y = 10 + (rand() % (height-20));
        
        [self dropStoneAtX:x Y:y withSize:RIPPLE_SIZE andWeight:RIPPLE_WEIGHT];
    } 
}





#pragma mark -- touches
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    for (UITouch *touch in touches) {
        CGPoint location = [touch locationInView:touch.view];
        NSLog(@"Ripple in point(x:%f, y:%f)",location.x, location.y);
        [self dropStoneAtX:location.x Y:location.y withSize:RIPPLE_SIZE andWeight:RIPPLE_WEIGHT];
    }
}


- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    NSArray *touchs = touches.allObjects;
    UITouch *startTouch = (UITouch *)touchs.firstObject;
    UITouch *endTouch = (UITouch *)touchs.lastObject;
    CGPoint startPoint = [startTouch locationInView:startTouch.view];
    CGPoint endPoint = [endTouch locationInView:endTouch.view];
    if (touchs.count <=1) {
        [self dropStoneAtX:startPoint.x Y:startPoint.y withSize:RIPPLE_SIZE andWeight:RIPPLE_WEIGHT];
    } else if (touchs.count > 1) {
        [self bresenhamDropSX:startPoint.x SY:startPoint.y EX:endPoint.x EY:endPoint.y withSize:RIPPLE_SIZE andWeight:RIPPLE_WEIGHT];
    }
}



/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
