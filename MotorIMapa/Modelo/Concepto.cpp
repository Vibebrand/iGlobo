/*
 * Concepto.cpp
 *
 *  Created on: 24/11/2011
 *      Author: LUIS.RANGEL
 */

#include "../API/Concepto.h"

namespace MotorIMapaAPI {
namespace modelo {

Concepto::Concepto() {
	nombre = "";
	tipo = "";
	nota = "";

	valores.clear();
	conceptos.clear();
	conceptoPredecesor = NULL;
}

Concepto::~Concepto() {
	nombre = "";
	tipo = "";
	nota = "";

	valores.clear();
	for(std::vector<Concepto *>::iterator it = conceptos.begin(); it != conceptos.end(); ++it) {
		Concepto * concepto = static_cast<Concepto *>(*it);
		delete concepto;
	}
	conceptos.clear();
	conceptoPredecesor = NULL;
}

std::string Concepto::toString() const {
	std::string salida = "";

	salida += "Concepto[" + nombre + "]-> tipo = " + tipo + " -> nota = " + nota + "\n";
	for(std::vector<Valor>::const_iterator it = valores.begin(); it != valores.end(); ++it) {
		Valor valor = static_cast<Valor>(*it);
		salida += "\tValor[" + valor.nombre + ", " + valor.tipo + "] = " + valor.valor + "\n";
	}

	for(std::vector<Concepto *>::const_iterator it = conceptos.begin(); it != conceptos.end(); ++it) {
		Concepto * conceptoInterno = static_cast<Concepto *>(*it);
		salida += "|_" + conceptoInterno->toString() + "\n";
	}

	salida += "\n";

	return salida;
}

} /* namespace modelo */
}
