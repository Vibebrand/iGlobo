/*
 * Concepto.h
 *
 *  Created on: 24/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef CONCEPTO_H_
#define CONCEPTO_H_

#include <string>
#include <vector>

#include "Valor.h"

namespace MotorIMapaAPI {
namespace modelo {

struct Concepto {
public:
	Concepto();
	virtual ~Concepto();
	virtual std::string toString() const;

	std::string nombre;
	std::string tipo;
	std::string nota;

	std::vector<Valor> valores;
	std::vector<Concepto *> conceptos;
	Concepto * conceptoPredecesor;
};

} /* namespace modelo */
}

#endif /* CONCEPTO_H_ */
