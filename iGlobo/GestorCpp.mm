//
//  GestorCpp.cpp
//  iGlobo
//
//  Created by Jesus Cagide on 05/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#include "GestorCpp.h"

GestorCpp::GestorCpp(id<iGestorObjectiveC> gestor, id<iControlMaestro> controlMaestro) {
    this->gestor = gestor;
    [this->gestor retain];
    
    this->controlMaestro = controlMaestro;
}

GestorCpp::~GestorCpp() {
    [this->gestor release];
}

void GestorCpp::procesaSeccion(MotorIMapaAPI::modelo::Seccion * seccion) {
    [gestor procesaSeccion: generaModelo(seccion)];
}

void GestorCpp::seccionInvalida(MotorIMapaAPI::modelo::Seccion * seccion) {
    [gestor seccionInvalida: generaModelo(seccion)];
}

void GestorCpp::finalizadaActualizacionSecciones() {
    [gestor finalizadaActualizacionSecciones];
}

std::set<std::string> GestorCpp::obtenNombreSeccionesGestionadas() {
    std::set<std::string> salida;
    NSArray * seccionesGestionadas = [gestor obtenNombreSeccionesGestionadas];
    NSEnumerator * it_seccionesGestionadas = [seccionesGestionadas objectEnumerator];
    id seccion = nil;
    while(seccion = [it_seccionesGestionadas nextObject]) {
        salida.insert([seccion UTF8String]);
    }
    
    return salida;
}

std::set<std::string> GestorCpp::obtenNombreSeccionesNoGestionadas() {
    std::set<std::string> salida;
    NSArray * seccionesNoGestionadas = [gestor obtenNombreSeccionesNoGestionadas];
    NSEnumerator * it_seccionesNoGestionadas = [seccionesNoGestionadas objectEnumerator];
    id seccion = nil;
    while(seccion = [it_seccionesNoGestionadas nextObject]) {
        salida.insert([seccion UTF8String]);
    }
    
    return salida;
}

void GestorCpp::registraMotor(MotorIMapaAPI::IMotorIMapa * motor) {
    this->motor = motor;
    [this->gestor registraControlMaestro: this->controlMaestro];
}

NSDictionary * GestorCpp::generaModelo(MotorIMapaAPI::modelo::Seccion * seccion) {
    NSMutableDictionary * salida = [[NSMutableDictionary new] autorelease];
    [salida setObject: obtenString(seccion->nombre)  forKey:@"nombre"];
    
    NSMutableDictionary * variables = [[NSMutableDictionary new] autorelease];
    [salida setObject:variables forKey: @"variables"];
    for(std::map<std::string, std::string>::iterator it_variables = seccion->variables.begin(); 
        it_variables != seccion->variables.end(); ++it_variables) {
        [variables setObject: obtenString(it_variables->second)  forKey: obtenString(it_variables->first)];
    }
    
    NSMutableArray * conceptos = [[NSMutableArray new] autorelease];
    [salida setObject: conceptos  forKey:@"conceptos"];
    
    for(std::vector<MotorIMapaAPI::modelo::Concepto *>::iterator it_conceptos = seccion->conceptos.begin();
        it_conceptos != seccion->conceptos.end(); ++it_conceptos) {
        [conceptos addObject: generaConceptos(*it_conceptos) ];
        
    }
    
    return salida;
}

NSDictionary * GestorCpp::generaConceptos(MotorIMapaAPI::modelo::Concepto * concepto) {
    NSMutableDictionary * concepto_map = [[NSMutableDictionary new] autorelease];
    [concepto_map setObject: obtenString(concepto->nombre)  forKey:@"nombre"];
    [concepto_map setObject: obtenString(concepto->tipo)  forKey:@"tipo"];
    [concepto_map setObject: obtenString(concepto->nota)  forKey:@"nota"];

    NSMutableArray * valores_array = [[NSMutableArray new] autorelease];
    [concepto_map setObject: valores_array forKey: @"valores"];
    
    for(std::vector<MotorIMapaAPI::modelo::Valor>::iterator it_valores = concepto->valores.begin();
        it_valores != concepto->valores.end(); ++it_valores) {
        MotorIMapaAPI::modelo::Valor valor = *it_valores;
        NSMutableDictionary * valor_map = [[NSMutableDictionary new] autorelease];
        
        [valor_map setObject: obtenString(valor.valor)  forKey: @"valor"];
        [valor_map setObject: obtenString(valor.tipo)  forKey: @"tipo"];
        [valor_map setObject: obtenString(valor.nombre)  forKey: @"nombre"];
        
        [valores_array addObject: valor_map];
    }
    
    NSMutableArray * conceptosInternos = [[NSMutableArray new] autorelease];
    for(std::vector<MotorIMapaAPI::modelo::Concepto *>::iterator it_conceptos = concepto->conceptos.begin();
        it_conceptos != concepto->conceptos.end(); ++it_conceptos) {
        MotorIMapaAPI::modelo::Concepto * conceptoInteres = *it_conceptos;
        
        NSDictionary * conceptoInterno = generaConceptos(conceptoInteres);
        [conceptosInternos addObject: conceptoInterno];
    }
    [concepto_map setObject: conceptosInternos forKey: @"conceptos"];
    
    return concepto_map;
}

NSString * GestorCpp::obtenString(std::string string) {
    return [NSString stringWithCString: string.c_str() encoding:NSUTF8StringEncoding];  
}