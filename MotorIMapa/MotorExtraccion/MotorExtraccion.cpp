/*
 * MotorExtraccion.cpp
 *
 *  Created on: 28/11/2011
 *      Author: LUIS.RANGEL
 */

#include "MotorExtraccion.h"


namespace MotorExtraccion {

IMotorExtraccion * IMotorExtraccion::_instance = 0;

MotorExtraccion::MotorExtraccion() {

}

MotorExtraccion::~MotorExtraccion() {
	// TODO Auto-generated destructor stub
}


IMotorExtraccion * IMotorExtraccion::instance() {
	if(_instance == 0) {
		_instance = new MotorExtraccion;
	}
	return _instance;
}

void MotorExtraccion::procesaArchivo(const char * archivo) {
	Servicios::ServicioParseo servicioParseo(archivo, &controladorSecciones);
}

IControladorSecciones * MotorExtraccion::obtenControladorSecciones() {
	return &controladorSecciones;
}
} /* namespace MotorIMapa */
