//
//  ControladorListaBarras.h
//  iGlobo
//
//  Created by Jesus Cagide on 29/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CeldaGraficaDeBarras.h"
#import "iControladorVista.h"


@interface ControladorListaBarras : UIViewController<UITableViewDelegate, UITableViewDataSource, iControladorVista>
{
    UITableView *_tablaDatos;
    //NSArray * _rangosDeEdad;
    CeldaGraficaDeBarras * _celdaBarras;
    UILabel * _porcentajeResultante;
    UINib *_cellNib;
}

#pragma iControladorVista
-(UIView *) obtenerRepresentacionBajoMarco:(CGRect) tamanioVentana;
-(UIView *) obtenerRepresentacion;

@property(nonatomic, retain) IBOutlet UITableView *tablaDatos;
@property(nonatomic, retain) IBOutlet UILabel * porcentajeResultante;
@property(nonatomic, retain) IBOutlet CeldaGraficaDeBarras * celdaBarras;
@property(nonatomic, retain) UINib * cellNib; 

@end
