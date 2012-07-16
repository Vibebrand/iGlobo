/*
 * ControladorSecciones.h
 *
 *  Created on: 24/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef CONTROLADORSECCIONES_H_
#define CONTROLADORSECCIONES_H_

#include <vector>
#include <string>

#include "../Servicios/Protocolos/IServicioParseoDelegado.h"
#include "../API/IControladorSecciones.h"

namespace MotorExtraccion {
namespace Controladores {

class ControladorSecciones : public IControladorSecciones, public IServicioParseoDelegado {
public:
	ControladorSecciones();
	virtual ~ControladorSecciones();

	std::string toString();

	// IControladorSecciones
	void asignarVariable(std::string variable, std::string valor);
	void eliminarVariable(std::string variable);
	void seccionesValidas(IControladorSeccionesDelegado * delegado);
	//

	// IServicioParseoDelegado
	void nuevaSeccion(MotorIMapaAPI::modelo::Seccion * seccion);
	//

private:
	std::vector<MotorIMapaAPI::modelo::Seccion *> secciones;
	std::map<std::string, std::string> variablesVigentes;
};

}
}

#endif /* CONTROLADORSECCIONES_H_ */
