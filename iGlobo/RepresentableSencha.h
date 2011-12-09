//
//  RepresentableSencha.h
//  iGlobo
//
//  Created by Jesus Cagide on 09/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#ifndef iGlobo_RepresentableSencha_h
#define iGlobo_RepresentableSencha_h

#include "IRepresentableSenchaDelegado.h"
#include "MotorSenchaAPI.h"

class RepresentableSencha : public MotorGraficasSencha::IRepresentableSencha {
public:
    RepresentableSencha(id<IRepresentableSenchaDelegado> delegado) {
        this->delegado = [delegado retain];
    }
    
    ~RepresentableSencha() {
        [delegado release];
    }
    
    bool requiereInicializacion();
	void vistaRequerida(bool requerida);
	void ejecutaInstruccion(const std::string instruccion);  
    
private:
    id<IRepresentableSenchaDelegado> delegado;
    
    NSString * obtenString(std::string string);
};

#endif
