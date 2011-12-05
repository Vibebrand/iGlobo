//
//  iGestorObjectiveC.h
//  iGlobo
//
//  Created by Jesus Cagide on 05/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "iControlMaestro.h"

@protocol iGestorObjectiveC <NSObject>

- (void) procesaSeccion: (NSDictionary *) seccion;
- (void) seccionInvalida: (NSDictionary *) seccion;
- (void) finalizadaActualizacionSecciones;
- (NSArray *) obtenNombreSeccionesGestionadas;
- (NSArray *) obtenNombreSeccionesNoGestionadas;
- (void) registraControlMaestro: (id<iControlMaestro>) controlMaestro;

@end
