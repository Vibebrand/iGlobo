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
@interface ControladorGraficaSencha : UIViewController<iControladorVista>


-(UIView *) obtenerRepresentacionBajoMarco:(CGRect) tamanioVentana;
-(UIView *) obtenerRepresentacion;

@property(nonatomic , assign)IBOutlet UILabel *etiquetaNombregrafica;
@property(nonatomic , assign)IBOutlet UIWebView *navegadorWeb;
@property(nonatomic, retain) ControladorSencha * controladorSencha;


@end
