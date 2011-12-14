//
//  PantallaPrincipal.h
//  iGlobo
//
//  Created by Jesus Cagide on 24/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ControladorRepresentacionGlobo.h"
#import "ControladorListaBarras.h"
#import "ControladorSencha.h"
#import "iControladorVista.h"
#import "ControladorPiramidePoblacional.h"
#import "ControladorSencha.h"

@interface PantallaPrincipal : UIViewController
{
    UIView * _representacionGlobo;
    UIView * _representacionGraficaBarrasIzquierdo;
    UIView * _representacionGraficaBarrasDerecha;
    id<iControladorVista> _controladorRepresentacionGlobo;
    
    
    ControladorListaBarras *_controladorRepresentacionListaGraficaBarrasIzquierda;
    ControladorListaBarras *_controladorRepresentacionListaGraficaBarrasDerecha;
    
    ControladorPiramidePoblacional * _controladorPiramidePoblacional;
    
    //id<iControladorVista> _controladorRepresentacionListaGraficaBarrasIzquierda;
    //id<iControladorVista> _controladorRepresentacionListaGraficaBarrasDerecha;

}

@property(nonatomic, retain) IBOutlet UIView* representacionGlobo;
@property(nonatomic, retain) IBOutlet UIView* representacionGraficaBarrasIzquierdo;
@property(nonatomic, retain) IBOutlet UIView* representacionGraficaBarrasDerecha;
@property(nonatomic, assign) IBOutlet UIWebView * webView;
@property(nonatomic, assign) IBOutlet UIWebView * webView2;

@property(nonatomic, retain) id<iControladorVista> controladorVista;
@property(nonatomic, retain) ControladorPiramidePoblacional *controladorPiramidePoblacional;
@property(nonatomic, retain) ControladorSencha * controladorSencha;
@property(nonatomic, retain) ControladorSencha * controladorSencha2;

@end
