/*
 * ControladorSecciones.cpp
 *
 *  Created on: 24/11/2011
 *      Author: LUIS.RANGEL
 */

#include "ControladorSecciones.h"

#ifdef IMPRIME_PARSEO
#include <iostream>
#endif

namespace MotorExtraccion {
namespace Controladores {

ControladorSecciones::ControladorSecciones() {
	secciones.clear();
	variablesVigentes.clear();
}

ControladorSecciones::~ControladorSecciones() {
	for(std::vector<MotorIMapaAPI::modelo::Seccion *>::iterator it = secciones.begin(); it != secciones.end(); ++it) {
		delete *it;
	}
	secciones.clear();
}


void ControladorSecciones::nuevaSeccion(MotorIMapaAPI::modelo::Seccion * seccion)
{
	secciones.push_back(seccion);
#ifdef IMPRIME_PARSEO
	std::clog << seccion->toString();
#endif
}

std::string ControladorSecciones::toString()
{
	std::string salida = "";

	for(std::vector<MotorIMapaAPI::modelo::Seccion *>::iterator it = secciones.begin(); it != secciones.end(); ++it) {
		MotorIMapaAPI::modelo::Seccion * seccion = static_cast<MotorIMapaAPI::modelo::Seccion *>(*it);
		salida += seccion->toString() + "\n----------------------------\n";
	}

	return salida;
}

void ControladorSecciones::asignarVariable(std::string variable, std::string valor) {
	this->variablesVigentes[variable] = valor;
}

void ControladorSecciones::eliminarVariable(std::string variable) {
	this->variablesVigentes.erase(variable);
}

void ControladorSecciones::seccionesValidas(IControladorSeccionesDelegado * delegado) {
	if(delegado) {
		for(std::vector<MotorIMapaAPI::modelo::Seccion *>::iterator it = secciones.begin(); it != secciones.end(); ++it) {
			MotorIMapaAPI::modelo::Seccion * seccion = static_cast<MotorIMapaAPI::modelo::Seccion *>(*it);
			bool seccionValida = true;

			// Revisar por cada filtro si es valido
			for(std::map<std::string, std::string>::iterator it_filtros = variablesVigentes.begin();
					seccionValida && it_filtros != variablesVigentes.end();
					++it_filtros) {

				std::string nombreFiltro = it_filtros->first;
				std::string valorFiltro = it_filtros->second;

				std::map<std::string, std::string>::iterator it_filtro_seccion = seccion->variables.find(nombreFiltro);
				if(it_filtro_seccion != seccion->variables.end()) {
					if(it_filtro_seccion->second != "" && it_filtro_seccion->second != valorFiltro) {

						delegado->seccionInvalida(seccion);
						seccionValida = false;
					}
				}
			}

			if(seccionValida) {
				delegado->seccionValida(seccion);
			}
		}
	}
}

}
}
