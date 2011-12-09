//
//  ControladorSencha.h
//  iGlobo
//
//  Created by Jesus Cagide on 09/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NativeBridge.h"
#import "NativeBridgeDelegate.h"

@interface ControladorSencha : UIViewController <NativeBridgeDelegate>
{
}

- (void)handleCall:(NSString*)functionName callbackId:(int)callbackId args:(NSArray*)args webView: (UIWebView *)webView andNativeBridge: (id<INativeBridge>) nativeBridge;

- (NSString*) pathForResource:(NSString*)resourcepath;

@property(nonatomic, assign) NativeBridge * nativeBridge;
@property(nonatomic, retain) IBOutlet UIWebView * webView;

@end
