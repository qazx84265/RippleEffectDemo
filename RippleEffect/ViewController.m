//
//  ViewController.m
//  RippleEffect
//
//  Created by 123 on 15/9/14.
//  Copyright (c) 2015年 com.pureLake. All rights reserved.
//

#import "ViewController.h"

#import "RippleView.h"

@interface ViewController () {
    
}
@property (nonatomic, strong) UIImageView *imageView;
@property (nonatomic, strong) RippleView *rippleView;
@property (nonatomic, strong) CADisplayLink *displayLink;
@end

@implementation ViewController
@synthesize rippleView = _rippleView;
@synthesize displayLink = _displayLink;

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    // Do any additional setup after loading the view, typically from a nib.

    
    _rippleView = [[RippleView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:_rippleView];

    
    //CADisplayLink
    _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    _displayLink.frameInterval = 2;
    [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}





- (void)render:(CADisplayLink*)displayLink {
//    [_rippleView raining];
    [_rippleView rippleSpread];
    [_rippleView rippleRender];
    
    //redraw
    [_rippleView setNeedsDisplay];
}






//#pragma mark -- touches
//- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
//    for (UITouch *touch in touches) {
//        CGPoint location = [touch locationInView:touch.view];
//        NSLog(@"Ripple in point(x:%f, y:%f)",location.x, location.y);
//        [_rippleView dropStoneAtX:location.x Y:location.y withSize:RIPPLE_SIZE andWeight:RIPPLE_WEIGHT];
//    }
//}






- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
