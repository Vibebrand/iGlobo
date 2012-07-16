//============================================================================
// Name        : MotorIMapa.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "MotorIMapa.h"

MotorIMapa::MotorIMapa() {
	motorExtraccion =  MotorExtraccion::IMotorExtraccion::instance();
}

MotorIMapa::~MotorIMapa() { 
    motorExtraccion = 0;
    gestoresRegistrados.clear();
    gestoresSecciones.clear();
}

void MotorIMapa::registraGestorSecciones(MotorIMapaAPI::IGestorSecciones * gestorSecciones) {

	// Agregar secciones gestionadas
	std::set<std::string> seccionesInteresGestionadas = gestorSecciones->obtenNombreSeccionesGestionadas();
	for(std::set<std::string>::iterator it_seccionesInteresGestionadas = seccionesInteresGestionadas.begin(); it_seccionesInteresGestionadas != seccionesInteresGestionadas.end(); ++it_seccionesInteresGestionadas) {
		std::string nombreSeccionInteres = static_cast<std::string>(*it_seccionesInteresGestionadas);
		gestoresSecciones[nombreSeccionInteres].insert(gestorSecciones);
	}

	// Eliminar secciones gestionadas
	std::set<std::string> seccionesInteresNoGestionadas = gestorSecciones->obtenNombreSeccionesNoGestionadas();
	for(std::set<std::string>::iterator it_seccionesInteresNoGestionadas = seccionesInteresNoGestionadas.begin(); it_seccionesInteresNoGestionadas != seccionesInteresNoGestionadas.end(); ++it_seccionesInteresNoGestionadas) {
		std::string nombreSeccionInteres = static_cast<std::string>(*it_seccionesInteresNoGestionadas);
		std::set<MotorIMapaAPI::IGestorSecciones *>::iterator it_gestoresPorSeccion = gestoresSecciones[nombreSeccionInteres].find(gestorSecciones);
		if(it_gestoresPorSeccion != gestoresSecciones[nombreSeccionInteres].end()) {
			gestoresSecciones[nombreSeccionInteres].erase(gestorSecciones);
		}
	}

	if(seccionesInteresGestionadas.size() > 0) {
		gestoresRegistrados.insert(gestorSecciones);
		gestorSecciones->registraMotor(this);
	} else {
		std::set<MotorIMapaAPI::IGestorSecciones *>::iterator it_gestorSecciones = gestoresRegistrados.find(gestorSecciones);
		if(it_gestorSecciones != gestoresRegistrados.end()) {
			gestoresRegistrados.erase(gestorSecciones);
		}
		gestorSecciones->registraMotor(0);
	}
}

void MotorIMapa::procesaArchivo(const char * rutaArchivo) {
	motorExtraccion->procesaArchivo(rutaArchivo);
}

void MotorIMapa::estableceCambioVariable(std::string nombre, std::string valor) {
	if(nombre.size() > 0) {
        motorExtraccion->obtenControladorSecciones()->asignarVariable(nombre, valor);
	}
}

void MotorIMapa::actualizaSecciones() {
	motorExtraccion->obtenControladorSecciones()->seccionesValidas(this);

	// Notificar gestores actualizacion finalizada
	for(std::set<MotorIMapaAPI::IGestorSecciones *>::iterator it_gestoresRegistrados = gestoresRegistrados.begin(); it_gestoresRegistrados != gestoresRegistrados.end(); ++it_gestoresRegistrados) {
		MotorIMapaAPI::IGestorSecciones * gestorInteres = static_cast<MotorIMapaAPI::IGestorSecciones *>(*it_gestoresRegistrados);
		gestorInteres->finalizadaActualizacionSecciones();
	}
}

void MotorIMapa::seccionValida(MotorIMapaAPI::modelo::Seccion * seccion) {
	std::map<std::string, std::set<MotorIMapaAPI::IGestorSecciones *> >::iterator it_gestorSecciones = gestoresSecciones.find(seccion->nombre);
	if(it_gestorSecciones != gestoresSecciones.end()) {
		std::set<MotorIMapaAPI::IGestorSecciones *> seccionesRegistradas = static_cast<std::set<MotorIMapaAPI::IGestorSecciones*> >(it_gestorSecciones->second);
		for(std::set<MotorIMapaAPI::IGestorSecciones *>::iterator it_seccionesRegistradas = seccionesRegistradas.begin(); it_seccionesRegistradas != seccionesRegistradas.end(); ++it_seccionesRegistradas) {
			MotorIMapaAPI::IGestorSecciones * gestorInteres = static_cast<MotorIMapaAPI::IGestorSecciones *>(*it_seccionesRegistradas);
			gestorInteres->procesaSeccion(seccion);
		}
	}
}

void MotorIMapa::seccionInvalida(MotorIMapaAPI::modelo::Seccion * seccion) {
	std::map<std::string, std::set<MotorIMapaAPI::IGestorSecciones *> >::iterator it_gestorSecciones = gestoresSecciones.find(seccion->nombre);
	if(it_gestorSecciones != gestoresSecciones.end()) {
		std::set<MotorIMapaAPI::IGestorSecciones *> seccionesRegistradas = static_cast<std::set<MotorIMapaAPI::IGestorSecciones*> >(it_gestorSecciones->second);
		for(std::set<MotorIMapaAPI::IGestorSecciones *>::iterator it_seccionesRegistradas = seccionesRegistradas.begin(); it_seccionesRegistradas != seccionesRegistradas.end(); ++it_seccionesRegistradas) {
			MotorIMapaAPI::IGestorSecciones * gestorInteres = static_cast<MotorIMapaAPI::IGestorSecciones *>(*it_seccionesRegistradas);
			gestorInteres->seccionInvalida(seccion);
		}
	}
}
