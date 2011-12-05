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
    [super dealloc];
}

@end
