//
//  iDelegadoControladorMapa.h
//  iGlobo
//
//  Created by Jesus Cagide on 18/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WhirlyGlobe/WhirlyGlobe.h>

@protocol iDelegadoControladorMapa <NSObject>

- (void)procesarBaseDeDatosVectorial;

-(void)cmdGeoReferenciaSeleccionada:(NSNotification *)notificacion;

-(WhirlyGlobeLayerThread *) obtenerlayerThread;

-(void)establecerlayerThread:(WhirlyGlobeLayerThread *) layerThread;

-(void)establecerScene:(WhirlyGlobe::GlobeScene *)scene;
@end
