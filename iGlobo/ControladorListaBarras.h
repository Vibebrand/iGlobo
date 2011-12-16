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
#import "CMPopTipView.h"

@interface ControladorListaBarras : UIViewController<UITableViewDelegate, UITableViewDataSource, iControladorVista, CMPopTipViewDelegate>
{
    UITableView *_tablaDatos;
    NSArray * _rangosDeEdad;
    CeldaGraficaDeBarras * _celdaBarras;
    UILabel * _porcentajeResultante;
    UILabel * _etiquetaNumeroTotalPorGenero;
    UINib *_cellNib;
    UIImageView *_imagen;
    NSString *_genero;
    
}

#pragma CMPopTipView

- (void)popTipViewWasDismissedByUser:(CMPopTipView *)popTipView;

#pragma iControladorVista
-(UIView *) obtenerRepresentacionBajoMarco:(CGRect) tamanioVentana;
-(UIView *) obtenerRepresentacion;

-(void) establcerGenero:(NSString*)genero;

-(void) establecerPorcentajeDeLaPoblacion:(NSString*) porcentajePoblacion enBaseAlaSumatoriaTotal:(NSString*)sumatorialTotal;

-(void) actualizarGrafica:(NSArray *) indicadoresGrafica;


@property(nonatomic, retain) IBOutlet UITableView *tablaDatos;
@property(nonatomic, retain) IBOutlet UILabel * porcentajeResultante;
@property(nonatomic, retain) IBOutlet UILabel *etiquetaNumeroTotalPorGenero;
@property(nonatomic, assign) IBOutlet UILabel *etiquetaReferenciaPopOver;
@property(nonatomic, retain) IBOutlet UIImageView * imagen;

@property (nonatomic, retain)	CMPopTipView * currentPopTipViewTarget;

@property(nonatomic, retain) IBOutlet CeldaGraficaDeBarras * celdaBarras;
@property(nonatomic, retain) UINib * cellNib;

@property(nonatomic, retain) NSString * genero;

@property(nonatomic, assign) NSArray* rangosDeEdad;

@end
