//
//  GestorCpp.h
//  iGlobo
//
//  Created by Jesus Cagide on 05/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#ifndef iGlobo_GestorCpp_h
#define iGlobo_GestorCpp_h

#import "MotorIMapaAPI.h"
#import "iControlMaestro.h"

#include "iGestorObjectiveC.h"

class GestorCpp : public MotorIMapaAPI::IGestorSecciones {
  
public:
    
    GestorCpp(id<iGestorObjectiveC> gestor, id<iControlMaestro> controlMaestro);
    ~GestorCpp();
    
    void procesaSeccion(MotorIMapaAPI::modelo::Seccion * seccion);
	void seccionInvalida(MotorIMapaAPI::modelo::Seccion * seccion);
	void finalizadaActualizacionSecciones();
    
	std::set<std::string> obtenNombreSeccionesGestionadas();
	std::set<std::string> obtenNombreSeccionesNoGestionadas();
    
	void registraMotor(MotorIMapaAPI::IMotorIMapa * motor);
    
private:
    id<iGestorObjectiveC> gestor;
    id<iControlMaestro> controlMaestro;
    
    MotorIMapaAPI::IMotorIMapa * motor;
    
    NSDictionary * generaModelo(MotorIMapaAPI::modelo::Seccion *);
    NSDictionary * generaConceptos(MotorIMapaAPI::modelo::Concepto *);
    NSString * obtenString(std::string string);
};

#endif
