//
//  ServicioMosaicoGeografico.h
//  iGlobo
//
//  Created by Jesus Cagide on 23/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "iServicioMosaicoGeografico.h"
#import "LoftLayer.h"
#import <map>

typedef std::map<std::string, WhirlyGlobe::SimpleIdentity> PoligonosDibujados;

enum accion{ AgregarPoligonos, EliminarPoligonos}; 

@interface ServicioMosaicoGeografico : NSObject<iServicioMosaicoGeografico>
{
    NSDictionary * _coloresBajoLeyenda;
    
    PoligonosBajoLeyenda  * _poligonosBajoLeyenda;

    LoftLayer * _capaDeDibujado;
    
    PoligonosDibujados  _poligonosBajoLeyendaDibujados;
    
}

-(id)initWithLoftLayer:(LoftLayer*) loftLayer;

-(void) accionSobrePoligonos:(accion) accion;

#pragma iServicioMosaicoGeografico

-(void)establecerPoligonosBajoLeyenda:(PoligonosBajoLeyenda *) poligonos; 
-(void) establecerColoresBajoLeyenda:(NSDictionary *)colores;
-(void) agregarPoligonosAlMapa;
-(void) agregarPoligonosBajoLeyenda:(NSString*)leyenda;

-(void) eliminarPoligonosDelMapa;
-(void) eliminarPoligonosBajoLeyenda:(NSString*)leyenda;

-( id<WhirlyGlobeLayer> ) obtenerCapaDeDibujado;

@property(nonatomic, retain) NSDictionary * coloresBajoLeyenda;

@property(nonatomic, retain) LoftLayer * capaDeDibujado;

@end
