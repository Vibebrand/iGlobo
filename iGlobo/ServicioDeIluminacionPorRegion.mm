//
//  ServicioDeIluminacionPorRegion.m
//  iGlobo
//
//  Created by Jesus Cagide on 25/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ServicioDeIluminacionPorRegion.h"

@implementation ServicioDeIluminacionPorRegion
@synthesize capaDeDibujado = _capaDeDibujado;


-(void) dealloc
{
    [_capaDeDibujado release];
    [super dealloc];
}

-(id)initWithLoftLayer:(LoftLayer*) loftLayer
{
    if ((self = [super init])) 
    {
        [self setCapaDeDibujado:loftLayer];
    }
    return self;
}

-( id<WhirlyGlobeLayer> ) obtenerCapaDeDibujado
{
    return _capaDeDibujado;
}

-(void) iluminarRegionBajoShapeSet:(WhirlyGlobe::ShapeSet *) shapeSet
{
    [self eliminarRegionIliminada];
    
    LoftedPolyDesc *loftCountryDesc = [[[LoftedPolyDesc alloc] init] autorelease];
    
    loftCountryDesc.color = [UIColor colorWithRed:0.4 green:0 blue:0.4 alpha:0.3];
     loftCountryDesc.height = 0.002;
    
    regionIluminada = [_capaDeDibujado addLoftedPolys:shapeSet desc:loftCountryDesc];
}

-(void) eliminarRegionIliminada
{
    if(regionIluminada > 0)
        [_capaDeDibujado removeLoftedPoly:regionIluminada];

}

@end
