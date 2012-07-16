/*
 * Valor.h
 *
 *  Created on: 24/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef VALOR_H_
#define VALOR_H_

#include <string>

namespace MotorIMapaAPI {
namespace modelo {

struct Valor {
public:
	Valor();
	virtual ~Valor();

	std::string nombre;
	std::string tipo;
	std::string valor;
};

} /* namespace modelo */
}

#endif /* VALOR_H_ */
