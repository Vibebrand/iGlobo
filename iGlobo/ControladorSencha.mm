//
//  ControladorSencha.m
//  iGlobo
//
//  Created by Jesus Cagide on 09/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ControladorSencha.h"
#import <QuartzCore/QuartzCore.h>

@implementation ControladorSencha

@synthesize webView;
@synthesize nativeBridge;
@synthesize nativeBridgeDelegate;
@synthesize vistaPrincipal;
- (id)init {
    self = [super init];
    if (self) {
        inicializado = false;
    }
    return self;
}

- (void)dealloc {
    [[self webView] setDelegate: nil];
    [self setWebView: nil];
    [self setNativeBridgeDelegate:nil];
    [super dealloc];
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [[self webView] setDelegate: [self nativeBridge]];
    [[self nativeBridge] setDelegate:[self nativeBridgeDelegate]];
    
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

- (void)handleCall:(NSString*)functionName callbackId:(int)callbackId args:(NSArray*)args webView: (UIWebView *)_webView andNativeBridge: (id<INativeBridge>) _nativeBridge {
    
    [[self nativeBridgeDelegate ] handleCall:functionName callbackId:callbackId args:args webView:_webView andNativeBridge:_nativeBridge];
}

- (bool) requiereInicializacion {
    // TODO Dar mas inteligencia a la inicializacion
    bool salida = inicializado;
    if(!inicializado)
        inicializado = true;
    return !salida;
}

- (void) estableceVistaRequerida: (bool) requerida {
    
    CATransition *transition = [CATransition animation];
    transition.duration = 0.90;
    transition.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    transition.type = kCATransitionFade;
    transition.delegate = self;
    [self.vistaPrincipal.layer addAnimation:transition forKey:nil];
    
    [self.vistaPrincipal setHidden:!requerida];
    [[self webView] setHidden: !requerida];
}

- (void) ejecutaInstruccion: (NSString *) instruccion {
    [[self webView] performSelectorOnMainThread:@selector(stringByEvaluatingJavaScriptFromString:) withObject: instruccion waitUntilDone: NO];
}

@end
