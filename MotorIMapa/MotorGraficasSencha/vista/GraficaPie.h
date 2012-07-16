/*
 * GraficaPie.h
 *
 *  Created on: 29/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef GRAFICAPIE_H_
#define GRAFICAPIE_H_

#include "../../API/Seccion.h"
#include "Grafica.h"

using namespace MotorIMapaAPI;

namespace MotorGraficasSencha {

class GraficaPie : public Grafica {
public:
	GraficaPie();
	virtual ~GraficaPie();

protected:
	std::string obtenDefinicionGrafica();
	void actualizaDefinicion(std::string &definicionActual, MotorIMapaAPI::modelo::Seccion * seccion, const std::string campoLlave, const std::string campoValor, const std::string campos, const std::string dataStore);

private:
	// Definicion de String de Grafica
	std::string definicionGrafica;
};

} /* namespace MotorGraficasSencha */
#endif /* GRAFICAPIE_H_ */
