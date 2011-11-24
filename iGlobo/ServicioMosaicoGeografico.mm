//
//  ServicioMosaicoGeografico.m
//  iGlobo
//
//  Created by Jesus Cagide on 23/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ServicioMosaicoGeografico.h"

@implementation ServicioMosaicoGeografico

@synthesize coloresBajoLeyenda = _coloresBajoLeyenda;
@synthesize capaDeDibujado = _capaDeDibujado;


-(void)dealloc
{
    self.coloresBajoLeyenda = nil;
    self.capaDeDibujado = nil;
    
    //for(PoligonosBajoLeyenda::iterator it= _poligonosBajoLeyenda.begin(); 
      //  it != _poligonosBajoLeyenda.end();++it)
    //{
      //  _poligonosBajoLeyenda.erase(it);
    //}
    
    [super dealloc];
}

-(id)initWithLoftLayer:(LoftLayer*) loftLayer
{
    if ((self = [super init])) 
    {
        _poligonosBajoLeyenda = nil;
        [self setCapaDeDibujado:loftLayer];
    }
    return self;
}

//cambiar este metodo
-(void)establecerPoligonosBajoLeyenda:(PoligonosBajoLeyenda *) poligonos
{
    _poligonosBajoLeyenda = poligonos;
}

-(void) establecerColoresBajoLeyenda:(NSDictionary *)colores
{
    [self setColoresBajoLeyenda:colores];
}

-( id<WhirlyGlobeLayer> ) obtenerCapaDeDibujado
{
    return _capaDeDibujado;
}


-(void) accionSobrePoligonos:(accion) accion
{
    NSEnumerator *enumerador = [_coloresBajoLeyenda keyEnumerator];
    id llave;
    while( (llave= [enumerador nextObject]))
    {
        switch (accion) {
            case AgregarPoligonos:
                [self agregarPoligonosBajoLeyenda:llave];
                break;
            case EliminarPoligonos:
                [self eliminarPoligonosBajoLeyenda:llave];
            default:
                break;
        }
    }
}

-(void) agregarPoligonosBajoLeyenda:(NSString*)leyenda
{
    PoligonosDibujados::iterator _it = _poligonosBajoLeyendaDibujados.find([leyenda UTF8String]);
    if( _it == _poligonosBajoLeyendaDibujados.end() )
    {
        NSLog(@"agregandoPoligono al loftlayer");
        LoftedPolyDesc *loftCountryDesc = [[[LoftedPolyDesc alloc] init] autorelease];
        
        loftCountryDesc.color = [[self coloresBajoLeyenda] objectForKey:leyenda];
        
        PoligonosBajoLeyenda::iterator it = _poligonosBajoLeyenda->find( [leyenda UTF8String] );
        if(it != _poligonosBajoLeyenda->end())
        {
            WhirlyGlobe::ShapeSet * figuras =it->second ;
            
            loftCountryDesc.height = 0.001;
            
             NSLog(@"agregando aa capaDibujado");
            _poligonosBajoLeyendaDibujados[[leyenda UTF8String]] = [_capaDeDibujado addLoftedPolys: figuras  desc:loftCountryDesc];
        }
    }
}

-(void) eliminarPoligonosBajoLeyenda:(NSString*)leyenda
{
    PoligonosDibujados::iterator it =  _poligonosBajoLeyendaDibujados.find([ leyenda UTF8String] );
    if( it != _poligonosBajoLeyendaDibujados.end())
    {
        [_capaDeDibujado removeLoftedPoly:it->second];
        _poligonosBajoLeyendaDibujados.erase(it);
    }
}

-(void) agregarPoligonosAlMapa
{
    [self accionSobrePoligonos:AgregarPoligonos];
}

-(void) eliminarPoligonosDelMapa
{
    [self accionSobrePoligonos:EliminarPoligonos];
}

@end
