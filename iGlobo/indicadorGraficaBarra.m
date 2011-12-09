//
//  indicadorGraficaBarra.m
//  iGlobo
//
//  Created by Jesus Cagide on 08/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "indicadorGraficaBarra.h"

@implementation indicadorGraficaBarra

@synthesize nombreEtiqueta = _nombreEtiqueta;
@synthesize porcentajeARepresentar = _porcentajeARepresentar;
@synthesize valor = _valor;
@synthesize tipoValor = _tipoValor;

-(void) dealloc
{
    [_nombreEtiqueta release];
    [super dealloc];
}

-(NSString*)description
{
    return [NSString stringWithFormat:@"%@ %.1f %.1f", [self nombreEtiqueta], [self valor], [self porcentajeARepresentar]];
}

@end
