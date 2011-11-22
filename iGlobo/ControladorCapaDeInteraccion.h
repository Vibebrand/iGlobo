//
//  ControladorCapaDeInteraccion.h
//  iGlobo
//
//  Created by Jesus Cagide on 18/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "iDelegadoControladorMapa.h"
#import <WhirlyGlobe/WhirlyGlobe.h>

@interface ControladorCapaDeInteraccion : NSObject<WhirlyGlobeLayer>
{
    id<iDelegadoControladorMapa> _delegadoControladorMapa;
}

-(void)cmdTocaLaPantalla:(NSNotification *)note;

-(void) registrarNotificaciones;

- (void)procesarBaseDeDatosVectorial:(id)sender;

#pragma WhirlyGlobeLayer
- (void)startWithThread:(WhirlyGlobeLayerThread *)inThread scene:(WhirlyGlobe::GlobeScene *)scene;


@property(nonatomic, retain) id<iDelegadoControladorMapa>  delegadoControladorMapa;

@end
