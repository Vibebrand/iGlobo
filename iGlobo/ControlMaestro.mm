//
//  ControlMaestro.m
//  iGlobo
//
//  Created by Jesus Cagide on 05/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ControlMaestro.h"
#include "MotorIMapa.h"


@implementation ControlMaestro

- (id)init {
    self = [super init];
    if (self) {
        motor = new MotorIMapa;
    }
    return self;
}

- (void)dealloc {
    delete motor;
    
    for(std::set<GestorCpp *>::iterator it_gestores = gestores.begin(); 
        it_gestores != gestores.end(); ++it_gestores) {
        delete *it_gestores;
    }
    gestores.clear();
    
    for(std::set<MotorIMapaAPI::IGestorSecciones *>::iterator it_gestores = gestoresCpp.begin(); 
        it_gestores != gestoresCpp.end(); ++it_gestores) {
        delete *it_gestores;
    }
    gestoresCpp.clear();
    
    [super dealloc];
}

- (void) registraGestor: (id<iGestorObjectiveC>) gestor {
    GestorCpp * gestorCppInteres = new GestorCpp(gestor, self);
    gestores.insert(gestorCppInteres);
    motor->registraGestorSecciones(gestorCppInteres);
}

- (void) registraGestorCpp: (MotorIMapaAPI::IGestorSecciones *) gestorSecciones {
    gestoresCpp.insert(gestorSecciones);
    motor->registraGestorSecciones(gestorSecciones);
}

- (void) estableceVariable:(NSString *) nombre valor: (NSString *) valor {
    motor->estableceCambioVariable([nombre UTF8String], [valor UTF8String]);
}

- (void) actualizaSecciones {
    motor->actualizaSecciones();
}

- (void) cargaArchivos {
    NSString * pathInteres = [[NSBundle mainBundle] bundlePath];
    NSArray * elementos = [NSBundle pathsForResourcesOfType: @"xml" inDirectory: pathInteres];
    NSEnumerator * it_elementos = [elementos objectEnumerator];
    id elemento = nil;
    while(elemento = [it_elementos nextObject]) {
        motor->procesaArchivo([elemento fileSystemRepresentation]);
    }
}

@end
