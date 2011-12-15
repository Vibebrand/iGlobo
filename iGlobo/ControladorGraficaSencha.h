//
//  ControladorGraficaSencha.h
//  iGlobo
//
//  Created by Jesus Cagide on 14/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ControladorSencha.h"
#import "iControladorVista.h"
#import "NativeBridgeDelegate.h"
@interface ControladorGraficaSencha : UIViewController<iControladorVista, NativeBridgeDelegate>


- (void)handleCall:(NSString*)functionName callbackId:(int)callbackId args:(NSArray*)args webView: (UIWebView *)webView andNativeBridge: (id<INativeBridge>) nativeBridge;

-(UIView *) obtenerRepresentacionBajoMarco:(CGRect) tamanioVentana;
-(UIView *) obtenerRepresentacion;
-(IBAction) accionarLeyendas:(id)sender;

@property(nonatomic , assign)IBOutlet UILabel *etiquetaNombregrafica;
@property(nonatomic , assign)IBOutlet UIWebView *navegadorWeb;
@property(nonatomic, retain) ControladorSencha * controladorSencha;


@end
