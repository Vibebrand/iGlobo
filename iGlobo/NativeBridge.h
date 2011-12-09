//
//  NativeBridge.h
//  iRSI
//
//  Created by Luis Alejandro Rangel Sánchez on 11/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NativeBridgeDelegate.h"

#import "INativeBridge.h"
#import "SBJson.h"

@interface NativeBridge : NSObject <INativeBridge, UIWebViewDelegate> {
    id<NativeBridgeDelegate> _delegate;
    SBJsonParser * parser;
    SBJsonWriter * writer;
}

- (id)init;
- (void)dealloc;

// -> UIWebViewDelegate
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType;

// -> INativeBridge
- (void)returnResult:(int)callbackId webView: (UIWebView *)webView args:(id)arg, ...;

@property(nonatomic, retain) id<NativeBridgeDelegate> delegate;
@end
