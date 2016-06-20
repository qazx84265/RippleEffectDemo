//
//  RippleView.h
//  RippleEffect
//
//  Created by 123 on 15/9/14.
//  Copyright (c) 2015年 com.pureLake. All rights reserved.
//

#import <UIKit/UIKit.h>




#define RIPPLE_SIZE 8
#define RIPPLE_WEIGHT 50



@interface RippleView : UIView
- (void)rippleSpread;
- (void)rippleRender;
- (void)raining;

- (void)dropStoneAtX:(int)x Y:(int)y withSize:(int)size andWeight:(int)weight;
- (void)bresenhamDropSX:(int)sx SY:(int)sy EX:(int)ex EY:(int)ey withSize:(int)size andWeight:(int)weight;
@end
