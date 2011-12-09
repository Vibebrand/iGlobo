//
//  RepresentableSencha.cpp
//  iGlobo
//
//  Created by Jesus Cagide on 09/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#include "RepresentableSencha.h"

bool RepresentableSencha::requiereInicializacion() {
    return [delegado requiereInicializacion];
}

void RepresentableSencha::vistaRequerida(bool requerida) {
    [delegado estableceVistaRequerida: requerida];
}

void RepresentableSencha::ejecutaInstruccion(const std::string instruccion) {
    [delegado ejecutaInstruccion: obtenString(instruccion)];
}

NSString * RepresentableSencha::obtenString(std::string string) {
    return [NSString stringWithCString: string.c_str() encoding:NSUTF8StringEncoding];  
}