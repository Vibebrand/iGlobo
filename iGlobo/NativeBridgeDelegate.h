//
//  NativeBridgeDelegate.h
//  iRSI
//
//  Created by Luis Alejandro Rangel Sánchez on 11/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "INativeBridge.h"

@protocol NativeBridgeDelegate <NSObject>

- (void)handleCall:(NSString*)functionName callbackId:(int)callbackId args:(NSArray*)args webView: (UIWebView *)webView andNativeBridge: (id<INativeBridge>) nativeBridge;

@end
