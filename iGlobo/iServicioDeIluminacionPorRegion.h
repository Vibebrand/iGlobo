//
//  iServicioDeIluminacionPorRegion.h
//  iGlobo
//
//  Created by Jesus Cagide on 25/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WhirlyGlobe/WhirlyGlobe.h>

@protocol iServicioDeIluminacionPorRegion <NSObject>

-(void) iluminarRegionBajoShapeSet:(WhirlyGlobe::ShapeSet *) shapeSet;
-(void) eliminarRegionIliminada;
-( id<WhirlyGlobeLayer> ) obtenerCapaDeDibujado;

@end
