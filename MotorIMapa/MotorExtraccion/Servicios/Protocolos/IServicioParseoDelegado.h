/*
 * IServicioParseoDelegado.h
 *
 *  Created on: 24/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef ISERVICIOPARSEODELEGADO_H_
#define ISERVICIOPARSEODELEGADO_H_

#include "../../../API/Seccion.h"

namespace MotorExtraccion {

class IServicioParseoDelegado {
public:
	virtual ~IServicioParseoDelegado() {}
	virtual void nuevaSeccion(MotorIMapaAPI::modelo::Seccion * seccion) = 0;
};
}

#endif /* ISERVICIOPARSEODELEGADO_H_ */
