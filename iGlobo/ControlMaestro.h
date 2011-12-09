//
//  ControlMaestro.h
//  iGlobo
//
//  Created by Jesus Cagide on 05/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "iControlMaestro.h"
#import "iGestorObjectiveC.h"

#include "GestorCpp.h"

#include <set>

struct MotorIMapa;

@interface ControlMaestro : NSObject<iControlMaestro>
{
    MotorIMapa * motor;
    
    std::set<GestorCpp *> gestores;
    std::set<MotorIMapaAPI::IGestorSecciones *> gestoresCpp;
}

- (void) registraGestor: (id<iGestorObjectiveC>) gestor;
- (void) registraGestorCpp: (MotorIMapaAPI::IGestorSecciones *) gestorSecciones;

- (void) estableceVariable:(NSString *) nombre valor: (NSString *) valor;
- (void) cargaArchivos;

@end
