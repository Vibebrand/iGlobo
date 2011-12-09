//
//  INativeBridge.h
//  iRSI
//
//  Created by Luis Alejandro Rangel Sánchez on 11/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@protocol INativeBridge <NSObject>

- (void)returnResult:(int)callbackId webView: (UIWebView *)webView args:(id)arg, ...;

@end
