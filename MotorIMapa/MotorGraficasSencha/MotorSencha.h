/*
 * MotorGraficasSencha.h
 *
 *  Created on: 30/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef MOTORGRAFICASSENCHA_H_
#define MOTORGRAFICASSENCHA_H_

#include "../API/IGestorSecciones.h"
#include "../API/IMotorIMapa.h"
#include "API/IRepresentableSecha.h"
#include "vista/Grafica.h"

#include "API/ServicioGeneradorInformacion.h"
#include "API/ServicioSerializadorInformacion.h"

#include <map>
#include <set>
#include <string>

namespace MotorGraficasSencha {

class MotorGraficasSencha : public MotorIMapaAPI::IGestorSecciones {
public:
    MotorGraficasSencha();
    ~MotorGraficasSencha();

    enum TipoGrafica {
    	Indefinido,
    	Pie,
    	Area
    };

	void procesaSeccion(MotorIMapaAPI::modelo::Seccion * seccion);
	void seccionInvalida(MotorIMapaAPI::modelo::Seccion * seccion);
	void finalizadaActualizacionSecciones();

	std::set<std::string> obtenNombreSeccionesGestionadas();
	std::set<std::string> obtenNombreSeccionesNoGestionadas();

	void registraMotor(MotorIMapaAPI::IMotorIMapa * motor);

	void registraRepresentable(IRepresentableSencha * representable, std::string nombreSeccion, TipoGrafica tipoGrafica);

private:
	ServicioGeneradorInformacion servicioGeneradorInformacion;
	ServicioSerializadorInformacion servicioSerializadorInformacion;

	// Gestionan relacion MotorSencha <-> IRepresentableSencha
    std::map<std::string, std::set<IRepresentableSencha *> > referenciaGraficas;
    std::map<IRepresentableSencha *, Grafica *> graficaPorRepresentable;

    // Cache de las secciones con su Modelo y Store
    std::map<MotorIMapaAPI::modelo::Seccion *, std::string> storePorSeccion;

    MotorIMapaAPI::IMotorIMapa * motor;

    std::set<IRepresentableSencha *> representablesActualizados;

    std::string obtenModeloPorSeccion(MotorIMapaAPI::modelo::Seccion * seccion, bool incluirCampoLlave);
    std::string obtenDataStorePorSeccion(MotorIMapaAPI::modelo::Seccion * seccion);
};

}

#endif /* MOTORGRAFICASSENCHA_H_ */
