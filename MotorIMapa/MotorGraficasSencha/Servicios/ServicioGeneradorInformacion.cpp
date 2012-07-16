/*
 * ServicioGeneradorModelo.cpp
 *
 *  Created on: 29/11/2011
 *      Author: LUIS.RANGEL
 */

#include "../API/ServicioGeneradorInformacion.h"

#include <set>
#include <algorithm>

namespace MotorGraficasSencha {

ServicioGeneradorInformacion::ServicioGeneradorInformacion(std::string campoLlave, std::string campoValorPredeterminado) : campoLlave(campoLlave), campoValorPredeterminado(campoValorPredeterminado) {
}

ServicioGeneradorInformacion::~ServicioGeneradorInformacion() {

}

std::vector<std::string> ServicioGeneradorInformacion::obtenCampos(MotorIMapaAPI::modelo::Seccion * seccion) {
	std::set<std::string> elementos;

	std::vector<MotorIMapaAPI::modelo::Concepto *> conceptos = seccion->conceptos;
	for(std::vector<MotorIMapaAPI::modelo::Concepto *>::const_iterator it_conceptos = conceptos.begin(); it_conceptos != conceptos.end(); ++it_conceptos) {
		MotorIMapaAPI::modelo::Concepto * concepto = static_cast<MotorIMapaAPI::modelo::Concepto *>(*it_conceptos);

		std::vector<MotorIMapaAPI::modelo::Valor> valores = concepto->valores;
		for(std::vector<MotorIMapaAPI::modelo::Valor>::const_iterator it_valores = valores.begin(); it_valores != valores.end(); ++it_valores) {
			MotorIMapaAPI::modelo::Valor valor = static_cast<MotorIMapaAPI::modelo::Valor>(*it_valores);
			std::string nombre = valor.nombre != "" ? valor.nombre : this->campoValorPredeterminado;

			elementos.insert(nombre);
		}
	}

	std::vector<std::string> salida(elementos.size());
	std::copy(elementos.begin(), elementos.end(), salida.begin());

	sort(salida.begin(), salida.end());

	return salida;
}

std::vector<std::map<std::string, std::string> > ServicioGeneradorInformacion::obtenStore(MotorIMapaAPI::modelo::Seccion * seccion) {
	std::vector<std::map<std::string, std::string> > salida;

	std::vector<MotorIMapaAPI::modelo::Concepto *> conceptos = seccion->conceptos;
	for(std::vector<MotorIMapaAPI::modelo::Concepto *>::const_iterator it_conceptos = conceptos.begin(); it_conceptos != conceptos.end(); ++it_conceptos) {
		MotorIMapaAPI::modelo::Concepto * concepto = static_cast<MotorIMapaAPI::modelo::Concepto *>(*it_conceptos);

		std::map<std::string, std::string> elementoSalida;
		elementoSalida[this->campoLlave] = concepto->nombre;

		std::vector<MotorIMapaAPI::modelo::Valor> valores = concepto->valores;
		for(std::vector<MotorIMapaAPI::modelo::Valor>::const_iterator it_valores = valores.begin(); it_valores != valores.end(); ++it_valores) {
			MotorIMapaAPI::modelo::Valor valor = static_cast<MotorIMapaAPI::modelo::Valor>(*it_valores);
			std::string nombre = valor.nombre != "" ? valor.nombre : this->campoValorPredeterminado;

			elementoSalida[nombre] = valor.valor;
		}

		salida.push_back(elementoSalida);
	}

	return salida;
}

} /* namespace MotorGraficasSencha */
