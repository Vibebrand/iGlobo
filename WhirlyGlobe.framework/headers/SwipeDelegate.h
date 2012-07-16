/*
 *  SwipeDelegate.h
 *  WhirlyGlobeLib
 *
 *  Created by Steve Gifford on 1/17/11.
 *  Copyright 2011 mousebird consulting
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#import <UIKit/UIKit.h>
#import "GlobeView.h"

/* Whirly Globe Swipe Delegate
	Responds to swipes and rotates the globe accordingly.
 */
@interface WhirlyGlobeSwipeDelegate : NSObject<UIGestureRecognizerDelegate>
{
	WhirlyGlobeView *view;
}

+ (WhirlyGlobeSwipeDelegate *)swipeDelegateForView:(UIView *)view globeView:(WhirlyGlobeView *)globeView;

@end
