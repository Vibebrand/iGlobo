//
//  iServicioMosaicoGeografico.h
//  iGlobo
//
//  Created by Jesus Cagide on 23/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WhirlyGlobe/WhirlyGlobe.h>


typedef std::map<std::string, WhirlyGlobe::ShapeSet *> PoligonosBajoLeyenda;
@protocol iServicioMosaicoGeografico <NSObject>

-(void)establecerPoligonosBajoLeyenda:(PoligonosBajoLeyenda *) poligonos;

-(void) establecerColoresBajoLeyenda:(NSDictionary *)colores;

-(void) agregarPoligonosAlMapa;

-(void) agregarPoligonosBajoLeyenda:(NSString*)leyenda;

-(void) eliminarPoligonosDelMapa;

-(void) eliminarPoligonosBajoLeyenda:(NSString*)leyenda;

-( id<WhirlyGlobeLayer> ) obtenerCapaDeDibujado;

@end
