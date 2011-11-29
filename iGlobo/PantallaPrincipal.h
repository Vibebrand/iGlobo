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
    id<iControladorVista> _controladorRepresentacionGlobo;
    id<iControladorVista> _controladorRepresentacionListaGraficaBarras;
}

@property(nonatomic, retain)IBOutlet UIView* representacionGlobo;
@property(nonatomic, retain)IBOutlet UIView* representacionGraficaBarrasIzquierdo;

@end
