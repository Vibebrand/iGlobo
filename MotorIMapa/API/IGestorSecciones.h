/*
 * IGestorSecciones.h
 *
 *  Created on: 30/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef IGESTORSECCIONES_H_
#define IGESTORSECCIONES_H_

#include <set>
#include <string>

#include "Seccion.h"

namespace MotorIMapaAPI {

class IMotorIMapa;

class IGestorSecciones {
public:
	virtual ~IGestorSecciones() {}

	virtual void procesaSeccion(modelo::Seccion * seccion) = 0;
	virtual void seccionInvalida(modelo::Seccion * seccion) = 0;
	virtual void finalizadaActualizacionSecciones() = 0;

	virtual std::set<std::string> obtenNombreSeccionesGestionadas() = 0;
	virtual std::set<std::string> obtenNombreSeccionesNoGestionadas() = 0;

	virtual void registraMotor(IMotorIMapa * motor) = 0;
};

}

#endif /* IGESTORSECCIONES_H_ */
