/*
 * Seccion.h
 *
 *  Created on: 24/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef SECCION_H_
#define SECCION_H_

#include <string>
#include <map>
#include <vector>

#include "Concepto.h"

namespace MotorIMapaAPI {
namespace modelo {

struct Seccion {
public:
	Seccion();
	virtual ~Seccion();
	virtual std::string toString() const;

	std::string nombre;
	std::map<std::string, std::string> variables;
	std::vector<Concepto *> conceptos;
};

}
} /* namespace modelo */
#endif /* SECCION_H_ */
