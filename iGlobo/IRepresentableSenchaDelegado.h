//
//  IRepresentableSenchaDelegado.h
//  iGlobo
//
//  Created by Jesus Cagide on 09/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol IRepresentableSenchaDelegado <NSObject>

-(bool) requiereInicializacion;
-(void) estableceVistaRequerida:(bool) requerida;
-(void) ejecutaInstruccion: (NSString *) instruccion;

@end
