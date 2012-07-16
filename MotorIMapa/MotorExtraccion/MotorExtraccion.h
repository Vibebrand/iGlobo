/*
 * MotorExtraccion.h
 *
 *  Created on: 28/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef MOTOREXTRACCION_H_
#define MOTOREXTRACCION_H_

#include "API/IMotorExtraccion.h"

#include "Servicios/ServicioParseo.h"
#include "Controladores/ControladorSecciones.h"

namespace MotorExtraccion {

class MotorExtraccion : public IMotorExtraccion {
public:
	MotorExtraccion();
	virtual ~MotorExtraccion();

	void procesaArchivo(const char * archivo);
	IControladorSecciones * obtenControladorSecciones();
private:
	Controladores::ControladorSecciones controladorSecciones;
};

} /* namespace MotorIMapa */
#endif /* MOTOREXTRACCION_H_ */
