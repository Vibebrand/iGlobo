//
//  ServicioDeIluminacionPorRegion.h
//  iGlobo
//
//  Created by Jesus Cagide on 25/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "iServicioDeIluminacionPorRegion.h"
#import <WhirlyGlobe/WhirlyGlobe.h>
#import "LoftLayer.h"

@interface ServicioDeIluminacionPorRegion : NSObject<iServicioDeIluminacionPorRegion>
{
    WhirlyGlobe::SimpleIdentity regionIluminada;
    LoftLayer * _capaDeDibujado;
}

-(id)initWithLoftLayer:(LoftLayer*) loftLayer;
-(void) iluminarRegionBajoShapeSet:(WhirlyGlobe::ShapeSet *) shapeSet;
-( id<WhirlyGlobeLayer> ) obtenerCapaDeDibujado;
-(void) eliminarRegionIliminada;

@property(nonatomic, assign) LoftLayer * capaDeDibujado;

@end
