//
//  ControladorSencha.m
//  iGlobo
//
//  Created by Jesus Cagide on 09/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ControladorSencha.h"

@implementation ControladorSencha

@synthesize webView;
@synthesize nativeBridge;

- (void)dealloc {
    [self setWebView: nil];
    [super dealloc];
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [[self webView] setDelegate: [self nativeBridge]];
    [[self nativeBridge] setDelegate: self];
    
    // Carga de html en webView
    NSString * startFilePath = [self pathForResource:@"index.html"];
    NSURL *appURL = [NSURL fileURLWithPath:startFilePath];
    NSURLRequest *appReq = [NSURLRequest requestWithURL:appURL cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:20.0];
    [[self webView] loadRequest:appReq];
}

- (NSString*) pathForResource:(NSString*)resourcepath
{
    NSBundle * mainBundle = [NSBundle mainBundle];
    NSMutableArray *directoryParts = [NSMutableArray arrayWithArray:[resourcepath componentsSeparatedByString:@"/"]];
    NSString       *filename       = [directoryParts lastObject];
    [directoryParts removeLastObject];
    
    NSString* directoryPartsJoined =[directoryParts componentsJoinedByString:@"/"];
    NSString* directoryStr = @"www";
    
    if ([directoryPartsJoined length] > 0) {
        directoryStr = [NSString stringWithFormat:@"%@/%@", @"www", [directoryParts componentsJoinedByString:@"/"]];
    }
    
    return [mainBundle pathForResource:filename
                                ofType:@""
                           inDirectory:directoryStr];
}

- (void)handleCall:(NSString*)functionName callbackId:(int)callbackId args:(NSArray*)args webView: (UIWebView *)webView andNativeBridge: (id<INativeBridge>) nativeBridge {
    
}

@end
