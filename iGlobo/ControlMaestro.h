//
//  ControlMaestro.h
//  iGlobo
//
//  Created by Jesus Cagide on 05/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "iGestorObjectiveC.h"

#include "GestorCpp.h"
#include <set>

struct MotorIMapa;

@interface ControlMaestro : NSObject
{
    MotorIMapa * motor;
    std::set<GestorCpp *> gestores;
}

- (void) registraGestor: (id<iGestorObjectiveC>) gestor;

@end
