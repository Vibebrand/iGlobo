//
//  GestorCpp.cpp
//  iGlobo
//
//  Created by Jesus Cagide on 05/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#include <iostream>
#include "GestorCpp.h"

GestorCpp::GestorCpp(id<iGestorObjectiveC> gestor) {
    this->gestor = gestor;
}


void GestorCpp::procesaSeccion(MotorIMapaAPI::modelo::Seccion * seccion) {
    
}

void GestorCpp::seccionInvalida(MotorIMapaAPI::modelo::Seccion * seccion) {
    
}

void GestorCpp::finalizadaActualizacionSecciones() {
    
}

std::set<std::string> GestorCpp::obtenNombreSeccionesGestionadas() {
    std::set<std::string> salida;
    
    return salida;
}

std::set<std::string> GestorCpp::obtenNombreSeccionesNoGestionadas() {
    std::set<std::string> salida;
    
    return salida;
}

void GestorCpp::registraMotor(MotorIMapaAPI::IMotorIMapa * motor) {
    
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
    [salida setObject: conceptos forKey: @"conceptos"];
    
    for(std::vector<MotorIMapaAPI::modelo::Concepto *>::iterator it_conceptos = seccion->conceptos.begin();
        it_conceptos != seccion->conceptos.end(); ++it_conceptos) {
        MotorIMapaAPI::modelo::Concepto * conceptoInteres = *it_conceptos;
        
        NSMutableDictionary * concepto_map = [[NSMutableDictionary new] autorelease];
        [concepto_map setObject: obtenString(conceptoInteres->nombre)  forKey:@"nombre"];
        [concepto_map setObject: obtenString(conceptoInteres->tipo)  forKey:@"tipo"];
        [concepto_map setObject: obtenString(conceptoInteres->nota)  forKey:@"nota"];
        
        NSMutableArray * valores_array = [[NSMutableArray new] autorelease];
        [concepto_map setObject: valores_array forKey: @"valores"];
        
        for(std::vector<MotorIMapaAPI::modelo::Valor>::iterator it_valores = conceptoInteres->valores.begin();
            it_valores != conceptoInteres->valores.end(); ++it_valores) {
            MotorIMapaAPI::modelo::Valor valor = *it_valores;
            NSMutableDictionary * valor_map = [[NSMutableDictionary new] autorelease];
            
            [valor_map setObject: obtenString(valor.valor)  forKey: @"valor"];
            [valor_map setObject: obtenString(valor.tipo)  forKey: @"tipo"];
            [valor_map setObject: obtenString(valor.nombre)  forKey: @"nombre"];
            
            [valores_array addObject: valor_map];
        }
        
        [conceptos addObject: concepto_map];
    }
    
    return salida;
}

// TODO Generar conceptos recursivos

NSString * GestorCpp::obtenString(std::string string) {
    return [NSString stringWithCString: string.c_str() encoding:NSISOLatin2StringEncoding];  
}