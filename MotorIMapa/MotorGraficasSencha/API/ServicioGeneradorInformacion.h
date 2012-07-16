/*
 * ServicioGeneradorModelo.h
 *
 *  Created on: 29/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef SERVICIOGENERADORMODELO_H_
#define SERVICIOGENERADORMODELO_H_

#include "../../API/Seccion.h"

#include <string>
#include <vector>
#include <map>

namespace MotorGraficasSencha {

class ServicioGeneradorInformacion {
public:
	ServicioGeneradorInformacion(std::string campoLlave = "campoLlave", std::string campoValorPredeterminado = "Porcentaje");
	virtual ~ServicioGeneradorInformacion();

	virtual std::vector<std::string> obtenCampos(MotorIMapaAPI::modelo::Seccion * seccion);
	virtual std::vector<std::map<std::string, std::string> > obtenStore(MotorIMapaAPI::modelo::Seccion * seccion);

	const std::string campoLlave;
	const std::string campoValorPredeterminado;
};

} /* namespace MotorGraficasSencha */
#endif /* SERVICIOGENERADORMODELO_H_ */
