//
//  ControladorMapa.m
//  iGlobo
//
//  Created by Jesus Cagide on 17/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ControladorMapa.h"

@implementation ControladorMapa

@synthesize layerThread = _layerThread;
@synthesize vectorLayer = _vectorLayer;
@synthesize labelLayer = _labelLayer;
@synthesize globeView = _globeView;
@synthesize servicioBDGeograficas = _servicioBDGeograficas;

-(void) dealloc
{
    self.layerThread = nil;
    self.globeView = nil;
    self.vectorLayer = nil;
    self.labelLayer = nil;
    
    for(RepresentacionesDePoligono::iterator it = _poligonosDibujados.begin(); it != _poligonosDibujados.end(); ++it)
        delete (*it);
    [_servicioBDGeograficas release];
    [super dealloc];
}
@end
