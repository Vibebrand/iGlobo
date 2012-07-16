/*
 * Seccion.cpp
 *
 *  Created on: 24/11/2011
 *      Author: LUIS.RANGEL
 */

#include "../API/Seccion.h"

namespace MotorIMapaAPI {
namespace modelo {

Seccion::Seccion() {
	nombre = "";
	variables.clear();
	conceptos.clear();
}

Seccion::~Seccion() {
	nombre = "";
	variables.clear();
	for(std::vector<Concepto *>::iterator it = conceptos.begin(); it != conceptos.end(); ++it) {
		Concepto * concepto = (Concepto * )(*it);
		delete concepto;
	}
	conceptos.clear();
}

std::string Seccion::toString() const {
	std::string salida = "";
	salida += "Seccion[" + nombre + "]\n";

	// Variables
	std::string variable = "";
	for(std::map<std::string, std::string>::const_iterator it = this->variables.begin(); it != this->variables.end(); ++it) {
		variable += "\t[" + it->first + "] =" + it->second + "\n";
	}

	if(variable.length() > 0) {
		salida += "Variables:\n" + variable;
	}

	std::string conceptosStr = "";
	for(std::vector<Concepto *>::const_iterator it = conceptos.begin(); it != conceptos.end(); ++it) {
		Concepto * concepto = static_cast<Concepto *>(*it);
		conceptosStr += concepto->toString();
	}

	if(conceptosStr.length() > 0) {
		salida += "Conceptos:\n" + conceptosStr;
	}

	salida += "\n";

	return salida;
}

} /* namespace modelo */
}
