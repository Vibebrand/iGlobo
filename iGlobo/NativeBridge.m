//
//  NativeBridge.m
//  iRSI
//
//  Created by Luis Alejandro Rangel Sánchez on 11/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NativeBridge.h"


@implementation NativeBridge

@synthesize delegate;
- (id)init
{
    if((self = [super init]))
    {
        parser = [SBJsonParser new];
        writer = [SBJsonWriter new];
    }
    
    return self;
}

- (void)dealloc
{
    [delegate release];
    [parser release];
    [writer release];
    
    [super dealloc];
}

// JS -> Objective-C
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    if(delegate != nil)
    {
        NSString *requestString = [[request URL] absoluteString];
        
        //NSLog(@"request : %@",requestString);
        
        if ([requestString hasPrefix:@"js-frame:"]) {
            
            NSArray *components = [requestString componentsSeparatedByString:@":"];
            
            NSString *function = (NSString*)[components objectAtIndex:1];
            int callbackId = [((NSString*)[components objectAtIndex:2]) intValue];
            NSString *argsAsString = [(NSString*)[components objectAtIndex:3] 
                                      stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
            
            NSArray *args = (NSArray*)[parser objectWithString:argsAsString error:nil];
            
            [delegate handleCall:function callbackId:callbackId args:args webView:webView andNativeBridge: self];
            
            return NO;
        }
    }
    
    return YES;
}

// Objective-C -> JS
- (void)returnResult:(int)callbackId webView: (UIWebView *)webView args:(id)arg, ...;
{
    if(webView != nil)
    {
        va_list argsList;
        NSMutableArray *resultArray = [[NSMutableArray alloc] init];
        
        if(arg != nil) {
            [resultArray addObject:arg];
            va_start(argsList, arg);
            while((arg = va_arg(argsList, id)) != nil)
                [resultArray addObject:arg];
            va_end(argsList);
        }
        
        NSString *resultArrayString = [writer stringWithObject:resultArray];
        NSString * callBackString = [NSString stringWithFormat:@"NativeBridge.resultForCallback(%d,%@);",callbackId,resultArrayString];
        NSLog(@"%@", callBackString);
        [webView performSelectorOnMainThread: @selector(stringByEvaluatingJavaScriptFromString:) withObject:callBackString waitUntilDone:false];
    } 
}

@end
