//
//  ControladorPiramidePoblacional.h
//  iGlobo
//
//  Created by Jesus Cagide on 08/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "iGestorObjectiveC.h"
#import "ControladorListaBarras.h"

@interface ControladorPiramidePoblacional : NSObject<iGestorObjectiveC>
{
    ControladorListaBarras *_controladorBarrasHombres;
    ControladorListaBarras *_controladorBarrasMujeres;
    
    NSMutableArray* hombres;
    NSMutableArray* mujeres;
    bool banderaValida;
}

-(void)procesarYActualizarGrafica;
-(float)sumatoriaArreglo:(NSArray*) arreglo;

#pragma iGestorObjectiveC
- (void) procesaSeccion: (NSDictionary *) seccion;
- (void) seccionInvalida: (NSDictionary *) seccion;
- (void) finalizadaActualizacionSecciones;
- (NSArray *) obtenNombreSeccionesGestionadas;
- (NSArray *) obtenNombreSeccionesNoGestionadas;
- (void) registraControlMaestro: (id<iControlMaestro>) controlMaestro;



@property(nonatomic, retain) ControladorListaBarras *controladorBarrasHombres;
@property(nonatomic, retain) ControladorListaBarras *controladorBarrasMujeres;
@end
