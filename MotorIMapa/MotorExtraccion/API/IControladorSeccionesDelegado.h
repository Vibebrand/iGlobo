/*
 * IControladorSeccionesDelegado.h
 *
 *  Created on: 28/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef ICONTROLADORSECCIONESDELEGADO_H_
#define ICONTROLADORSECCIONESDELEGADO_H_

#include "../../API/Seccion.h"

namespace MotorExtraccion {

class IControladorSeccionesDelegado {
public:
	virtual ~IControladorSeccionesDelegado() {}

	virtual void seccionValida(MotorIMapaAPI::modelo::Seccion * seccion) = 0;
	virtual void seccionInvalida(MotorIMapaAPI::modelo::Seccion * seccion) = 0;
};

} /* namespace MotorIMapa */
#endif /* ICONTROLADORSECCIONESDELEGADO_H_ */
