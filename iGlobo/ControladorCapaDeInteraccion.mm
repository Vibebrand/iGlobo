//
//  ControladorCapaDeInteraccion.m
//  iGlobo
//
//  Created by Jesus Cagide on 18/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ControladorCapaDeInteraccion.h"

@implementation ControladorCapaDeInteraccion

#pragma  Synthesize

@synthesize delegadoControladorMapa= _delegadoControladorMapa;

-(id)init
{    
    return self;
}

-(void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_delegadoControladorMapa release];
    [self dealloc];
}

- (void)startWithThread:(WhirlyGlobeLayerThread *)inThread scene:(WhirlyGlobe::GlobeScene *)scene
{
    [_delegadoControladorMapa establecerlayerThread:inThread];
    
    [self performSelector:@selector(process:) onThread:[_delegadoControladorMapa obtenerlayerThread] withObject:nil waitUntilDone:NO];

}

-(void) registrarNotificaciones
{
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(cmdTocaLaPantalla:) name:WhirlyGlobeTapMsg object:nil];
}

-(void)cmdTocaLaPantalla:(NSNotification *)note
{
    [[self delegadoControladorMapa] cmdGeoReferenciaSeleccionada:note];
}

- (void)procesarBaseDeDatosVectorial:(id)sender
{
    [[self delegadoControladorMapa] procesarBaseDeDatosVectorial];
    [self performSelector:@selector(procesarBaseDeDatosVectorial:) onThread:[_delegadoControladorMapa obtenerlayerThread] withObject:nil waitUntilDone:NO];
}


@end
