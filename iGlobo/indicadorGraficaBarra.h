//
//  indicadorGraficaBarra.h
//  iGlobo
//
//  Created by Jesus Cagide on 08/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface indicadorGraficaBarra : NSObject
{
    NSString * _nombreEtiqueta;
    float _valor;
    float _tipoValor;
    float _porcentajeARepresentar;
    float _porcentajeSegunValor;
}

-(NSString*)description;

@property(nonatomic, retain) NSString * nombreEtiqueta;
@property(nonatomic, assign) float porcentajeARepresentar;
@property(nonatomic, assign) float valor;
@property(nonatomic, assign) float tipoValor;
@property(nonatomic, assign) float porcentajeSegunValor;

@end
