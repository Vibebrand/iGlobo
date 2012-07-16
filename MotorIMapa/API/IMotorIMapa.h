/*
 * IMotorIMapa.h
 *
 *  Created on: 30/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef IMOTORIMAPA_H_
#define IMOTORIMAPA_H_

#include "IGestorSecciones.h"

#include <string>

namespace MotorIMapaAPI {

class IMotorIMapa {
public:
	virtual ~IMotorIMapa(){}

	virtual void registraGestorSecciones(IGestorSecciones * gestorSecciones) = 0;

	virtual void procesaArchivo(const char * rutaArchivo) = 0;
	virtual void estableceCambioVariable(std::string nombre, std::string valor) = 0;
	virtual void actualizaSecciones() = 0;
};

}

#endif /* IMOTORIMAPA_H_ */
