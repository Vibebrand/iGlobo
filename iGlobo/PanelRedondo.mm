//
//  PanelRedondo.m
//  iGlobo
//
//  Created by Jesus Cagide on 25/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "PanelRedondo.h"
#import <QuartzCore/QuartzCore.h>

@implementation PanelRedondo

- (id)initWithFrame:(CGRect)frame
{
    if ((self = [super initWithFrame:frame])) {
        // Initialization code
		[self setBackgroundColor:[UIColor blackColor]];
		[self setAlpha:1];
		[[self layer] setCornerRadius:10];
		[[self layer] setMasksToBounds:NO]; 
		[[self layer] setShadowColor:[UIColor blackColor].CGColor];
		[[self layer] setShadowOpacity:1.0f];
		[[self layer] setShadowRadius:6.0f];
		[[self layer] setShadowOffset:CGSizeMake(0, 3)];
    }
    return self;
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
