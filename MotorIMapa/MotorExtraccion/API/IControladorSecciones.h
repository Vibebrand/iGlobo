/*
 * IControladorSecciones.h
 *
 *  Created on: 28/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef ICONTROLADORSECCIONES_H_
#define ICONTROLADORSECCIONES_H_

#include "IControladorSeccionesDelegado.h"

namespace MotorExtraccion {

class IControladorSecciones {
public:
	virtual ~IControladorSecciones() {}

	virtual void asignarVariable(std::string variable, std::string valor) = 0;
	virtual void eliminarVariable(std::string variable) = 0;
	virtual void seccionesValidas(IControladorSeccionesDelegado * delegado) = 0;
};

}

#endif /* ICONTROLADORSECCIONES_H_ */
