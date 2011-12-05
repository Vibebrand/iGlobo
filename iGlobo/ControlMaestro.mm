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
    
    [super dealloc];
}

- (void) registraGestor: (id<iGestorObjectiveC>) gestor {
    GestorCpp * gestorCppInteres = new GestorCpp(gestor);
    gestores.insert(gestorCppInteres);
    motor->registraGestorSecciones(gestorCppInteres);
}

@end
