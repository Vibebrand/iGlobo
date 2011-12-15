//
//  ControladorPiramidePoblacional.m
//  iGlobo
//
//  Created by Jesus Cagide on 08/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ControladorPiramidePoblacional.h"
#import "indicadorGraficaBarra.h"

@implementation ControladorPiramidePoblacional

@synthesize controladorBarrasHombres = _controladorBarrasHombres;
@synthesize controladorBarrasMujeres = _controladorBarrasMujeres;

-(void) dealloc
{
    [_controladorBarrasHombres release];
    [_controladorBarrasMujeres release];
    [hombres release];
    [mujeres release];
}

-(id)init
{
    hombres = [NSMutableArray new];
    mujeres = [NSMutableArray new];
    banderaValida = NO;
    return self;
}


-(void)procesarYActualizarGrafica
{
    float sumatoriaHombres = [self sumatoriaArreglo:hombres];
    float sumatoriaMujeres = [self sumatoriaArreglo:mujeres];
    
    float sumtoriaTotal = sumatoriaHombres +  sumatoriaMujeres;
    
    [_controladorBarrasHombres establecerPorcentajeDeLaPoblacion:[NSString stringWithFormat:@"%.1f%%", ( (sumatoriaHombres*100)/sumtoriaTotal )] enBaseAlaSumatoriaTotal:[NSString stringWithFormat:@"%.0f Mil", sumatoriaHombres]];
    
    [_controladorBarrasMujeres establecerPorcentajeDeLaPoblacion:[NSString stringWithFormat:@"%.1f%%", ( (sumatoriaMujeres*100)/sumtoriaTotal )] enBaseAlaSumatoriaTotal:[NSString stringWithFormat:@"%.0f Mil", sumatoriaMujeres]];
    
    [_controladorBarrasHombres actualizarGrafica:hombres];
    [_controladorBarrasMujeres actualizarGrafica:mujeres];
}

-(float)sumatoriaArreglo:(NSArray*) arreglo
{
    float sumatoria=0.0f;
    float numeroMayor=0.0f;
    NSEnumerator *registro = [arreglo objectEnumerator];
    indicadorGraficaBarra *indicador;
    while(indicador =  [registro nextObject] )
    {
        sumatoria += [indicador valor];
        if(numeroMayor <  [indicador valor])
            numeroMayor = [indicador valor];
    }
    NSInteger numeroElementos = [arreglo count];
    for(int i=0; i< numeroElementos; i++)
    {
        indicador = [arreglo objectAtIndex:i];
        [indicador setPorcentajeARepresentar: ([indicador valor] /numeroMayor) ];        
    }
    return sumatoria;
}

#pragma iGestorObjectiveC

- (void) procesaSeccion: (NSDictionary *) seccion
{
    [mujeres removeAllObjects];
    [hombres removeAllObjects];
    
    NSArray *datosPoblacionales =  [seccion objectForKey:@"conceptos"];
    NSEnumerator *dato = [datosPoblacionales objectEnumerator];
    id datoDiccionario;
    while(datoDiccionario = [dato nextObject] )
    {
        NSString * nombre = [datoDiccionario objectForKey:@"nombre"];
        id listaValor = [datoDiccionario objectForKey:@"valores"];
        NSEnumerator *valores = [listaValor objectEnumerator] ;
        id diccionarioValores;
        while( diccionarioValores = [valores nextObject]  )
        {
            indicadorGraficaBarra *indicador = [indicadorGraficaBarra new];
            NSString * valor = [diccionarioValores objectForKey:@"valor"];
           
            [indicador setNombreEtiqueta: nombre];
            NSString * nombreSeccion = [diccionarioValores objectForKey:@"nombre"];
            [indicador setValor: [valor floatValue]];
            
            if([nombreSeccion isEqualToString:@"Hombres"])
                [hombres addObject:indicador];
            
            if([nombreSeccion isEqualToString:@"Mujeres"])
                [mujeres addObject:indicador];
        }
    }
    [self procesarYActualizarGrafica];
    banderaValida = YES;
}
- (void) seccionInvalida: (NSDictionary *) seccion
{
}
- (void) finalizadaActualizacionSecciones
{
    if(!banderaValida)
    {
        [mujeres removeAllObjects];
        [hombres removeAllObjects];
        
        [_controladorBarrasHombres establecerPorcentajeDeLaPoblacion:@"0.0%" enBaseAlaSumatoriaTotal:@"0.0"];
        
        [_controladorBarrasMujeres establecerPorcentajeDeLaPoblacion:@"0.0%" enBaseAlaSumatoriaTotal:@"0.0"];
        
        [_controladorBarrasHombres actualizarGrafica:hombres];
        [_controladorBarrasMujeres actualizarGrafica:mujeres];
    }
    banderaValida = NO;
}


- (NSArray *) obtenNombreSeccionesGestionadas
{
    return [NSArray arrayWithObject: @"Piramide poblacional"];
}


- (NSArray *) obtenNombreSeccionesNoGestionadas
{
    return [NSArray arrayWithObject: @""];
}

- (void) registraControlMaestro: (id<iControlMaestro>) controlMaestro{}


@end
