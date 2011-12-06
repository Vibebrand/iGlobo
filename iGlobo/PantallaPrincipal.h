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
#import "iControladorVista.h"

@interface PantallaPrincipal : UIViewController
{
    UIView * _representacionGlobo;
    UIView * _representacionGraficaBarrasIzquierdo;
    UIView * _representacionGraficaBarrasDerecha;
    id<iControladorVista> _controladorRepresentacionGlobo;
    
    
    ControladorListaBarras *_controladorRepresentacionListaGraficaBarrasIzquierda;
    ControladorListaBarras *_controladorRepresentacionListaGraficaBarrasDerecha;
    
    //id<iControladorVista> _controladorRepresentacionListaGraficaBarrasIzquierda;
    //id<iControladorVista> _controladorRepresentacionListaGraficaBarrasDerecha;

}

@property(nonatomic, retain) IBOutlet UIView* representacionGlobo;
@property(nonatomic, retain) IBOutlet UIView* representacionGraficaBarrasIzquierdo;
@property(nonatomic, retain) IBOutlet UIView* representacionGraficaBarrasDerecha;
@property(nonatomic, retain) id<iControladorVista> controladorVista;

@end
