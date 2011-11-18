//
//  ControladorMapa.h
//  iGlobo
//
//  Created by Jesus Cagide on 17/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//
#import <Foundation/Foundation.h>

struct PunteroRepresentacionPoligono;
struct PunteroVectorAreaRef;
struct PunteroShapeSet;

//Pendiente refactoring basado en Pimpl
@protocol iControladorMapa <NSObject>

-(PunteroRepresentacionPoligono *) agregarOceano: (PunteroVectorAreaRef*) area;
-(PunteroRepresentacionPoligono *) agregarPais:(NSDictionary*) arDict;
-(void) agregarEstados:(PunteroRepresentacionPoligono*) poligono conPoligonos:(PunteroShapeSet *) regionShapes;
-(void)eliminarRepresentacionPoligono:(PunteroRepresentacionPoligono *) poligono;
//signal
-(void)cmdGeoReferenciaSeleccionada;

@end
