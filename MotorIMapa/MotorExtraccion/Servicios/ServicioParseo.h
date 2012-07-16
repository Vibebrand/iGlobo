/*
 * ServicioParseo.h
 *
 *  Created on: 23/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef SERVICIOPARSEO_H_
#define SERVICIOPARSEO_H_

#include "LectorXML.h"

#include "../../API/Seccion.h"


#include "Protocolos/IServicioParseoDelegado.h"

#include <vector>
#include <string>
#include <map>
#include <sstream>

namespace MotorExtraccion {
namespace Servicios {

struct  ElementoLeido {
	enum TipoElementoLeido {
		ELEMENTO,
		ATRIBUTO
	};

	TipoElementoLeido type;
	int depth;
	int nodeType;
	int isEmptyElement;
	int hasValue;
	int hasAttributes;

	std::string constName;
	std::string constValue;
};

class ServicioParseo {
public:
	ServicioParseo(const char * nombreArchivo, IServicioParseoDelegado * delegado = NULL);
	virtual ~ServicioParseo();

	enum EstadoParseo {
		ESPERA,
		AGREGANDO_CONJUNTO,
		AGREGANDO_CONJUNTO_VARIABLES,
		AGREGANDO_CONJUNTO_VARIABLES_CONCEPTO,
		AGREGANDO_SECCION,
		AGREGANDO_SECCION_CONCEPTO,
		AGREGANDO_SECCION_CONCEPTO_VALOR
	};

	void agregarElemento(ElementoLeido elementoLeido);

private:
	IServicioParseoDelegado * delegado;

	std::vector<std::string> nombreConjuntos;
	std::map<std::string, std::map<std::string, std::string> > variables;

	EstadoParseo estadoActual;

	std::string nombreConceptoActual;
	MotorIMapaAPI::modelo::Seccion * seccionActual;
	MotorIMapaAPI::modelo::Concepto * conceptoActual;
	std::string nombreValorActual;

	bool estadoAgregarTipos;
	std::vector<std::string> tiposConceptos;
	std::vector<std::string> tiposValores;

	void llenarVariablesEnSeccionActual();
};

}
}

#endif /* SERVICIOPARSEO_H_ */
