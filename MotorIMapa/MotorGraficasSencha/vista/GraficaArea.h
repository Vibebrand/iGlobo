/*
 * GraficaPie.h
 *
 *  Created on: 29/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef GRAFICAAREA_H_
#define GRAFICAAREA_H_

#include "../../API/Seccion.h"
#include "Grafica.h"

using namespace MotorIMapaAPI;

namespace MotorGraficasSencha {

class GraficaArea : public Grafica {
public:
	GraficaArea();
	virtual ~GraficaArea();

protected:
	std::string obtenDefinicionGrafica();
	void actualizaDefinicion(std::string &definicionActual, MotorIMapaAPI::modelo::Seccion * seccion, const std::string campoLlave, const std::string campoValor, const std::string campos, const std::string dataStore);

private:
	// Definicion de String de Grafica
	std::string definicionGrafica;
};

} /* namespace MotorGraficasSencha */
#endif /* GRAFICAAREA_H_ */
