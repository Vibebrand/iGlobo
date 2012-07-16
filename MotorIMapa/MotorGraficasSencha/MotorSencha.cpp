//============================================================================
// Name        : MotorGraficasSencha.cpp
// Author      :
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "MotorSencha.h"
#include "vista/GraficaPie.h"
#include "vista/GraficaArea.h"

#include <iostream>
#include "stdlib.h"

// TODO Generar comportamiento polimorfico entre graficas
// TODO Lectura de info de grafica a partir de archivo: http://stackoverflow.com/questions/4313759/files-in-folders-not-found-in-ios-app-using-c
// TODO Hacer a toda seccion inmutable
namespace MotorGraficasSencha {

MotorGraficasSencha::MotorGraficasSencha() {
}

MotorGraficasSencha::~MotorGraficasSencha() {
	// Eliminar graficas de elementos representables...
	for(std::map<IRepresentableSencha *, Grafica *>::iterator it_graficas = graficaPorRepresentable.begin();
			it_graficas != graficaPorRepresentable.end(); ++it_graficas) {
		if(it_graficas->second)
			delete it_graficas->second;
	}
	graficaPorRepresentable.clear();
}

void MotorGraficasSencha::procesaSeccion(MotorIMapaAPI::modelo::Seccion * seccion) {
	std::map<std::string, std::set<IRepresentableSencha *> >::iterator it_encontradosRepresentables = referenciaGraficas.find(seccion->nombre);
	if(it_encontradosRepresentables != referenciaGraficas.end()) {
		std::string campos = obtenModeloPorSeccion(seccion, false);
		std::string camposCampoLlave = obtenModeloPorSeccion(seccion, true);
		std::string dataStore = obtenDataStorePorSeccion(seccion);

		std::set<IRepresentableSencha *> representables = it_encontradosRepresentables->second;
		for(std::set<IRepresentableSencha *>::iterator it_representables = representables.begin();
				it_representables != representables.end(); ++it_representables) {

			IRepresentableSencha * representableInteres = *it_representables;
			Grafica * graficaInteres = 0;
			std::map<IRepresentableSencha *, Grafica *>::iterator it_graficas = graficaPorRepresentable.find(representableInteres);
			if(it_graficas != graficaPorRepresentable.end()) {
				graficaInteres = it_graficas->second;
			} else { // TODO Considerar Grafica predeterminada
				std::cerr << "Grafica no valida" << std::endl;
				exit(1);
			}

			if(graficaInteres) {
				representablesActualizados.insert(representableInteres);
				representableInteres->vistaRequerida(true);

				// Enviar JS a IRepresentableSeleccion
				if(representableInteres->requiereInicializacion()) {
					std::string instruccionModelo = graficaInteres->obtenInstruccionModelo(seccion, camposCampoLlave);
					std::string instruccionStore = graficaInteres->obtenInstruccionStore(seccion, dataStore, false);
					std::string instruccionGrafica = graficaInteres->obtenInstruccionGrafica(seccion,
							servicioGeneradorInformacion.campoLlave,
							servicioGeneradorInformacion.campoValorPredeterminado,
							campos,
							dataStore);

					representableInteres->ejecutaInstruccion(instruccionModelo);
					representableInteres->ejecutaInstruccion(instruccionStore);
					representableInteres->ejecutaInstruccion(instruccionGrafica);

				} else {
					std::string instruccionStore = graficaInteres->obtenInstruccionStore(seccion, dataStore, true);
					representableInteres->ejecutaInstruccion(instruccionStore);
				}
			} else { // TODO Considerar Grafica predeterminada
				std::cerr << "Grafica no valida" << std::endl;
				exit(1);
			}
		}
	}
}

void MotorGraficasSencha::seccionInvalida(MotorIMapaAPI::modelo::Seccion * seccion) {
    std::cout << "MotorGraficasSencha::seccionInvalida: " << seccion->nombre;
}

void MotorGraficasSencha::finalizadaActualizacionSecciones() {

    // Notificar a todos los representables que no esten en representablesActualizados que no requieren ser representados
	for(std::map<IRepresentableSencha *, Grafica *>::iterator it = graficaPorRepresentable.begin();
			it != graficaPorRepresentable.end(); ++it) {
		std::set<IRepresentableSencha *>::iterator it_representableFueActualizado =  representablesActualizados.find(it->first);
		if(it_representableFueActualizado == representablesActualizados.end()) {
			it->first->vistaRequerida(false);
		}
	}

	representablesActualizados.clear();
}

std::set<std::string> MotorGraficasSencha::obtenNombreSeccionesGestionadas() {
    std::set<std::string> salida;
    for(std::map<std::string, std::set<IRepresentableSencha *> >::iterator it = referenciaGraficas.begin();
    		it != referenciaGraficas.end(); ++it) {
    	salida.insert(it->first);
    }
    return salida;
}

std::set<std::string> MotorGraficasSencha::obtenNombreSeccionesNoGestionadas() {
    std::set<std::string> salida;

    return salida;
}

void MotorGraficasSencha::registraMotor(MotorIMapaAPI::IMotorIMapa * motor) {
	this->motor = motor;
}

void MotorGraficasSencha::registraRepresentable(IRepresentableSencha * representable, std::string nombreSeccion, TipoGrafica tipoGrafica) {
	referenciaGraficas[nombreSeccion].insert(representable);
	std::map<IRepresentableSencha *, Grafica *>::iterator it = graficaPorRepresentable.find(representable);
	if(it != graficaPorRepresentable.end())
		delete it->second;

	Grafica * graficaInteres = 0;
	switch (tipoGrafica) {
	case Indefinido:
		break;
	case Pie:
		graficaInteres = new GraficaPie;
		break;
	case Area:
		graficaInteres = new GraficaArea;
		break;
	}

	graficaPorRepresentable[representable] = graficaInteres;
}

std::string MotorGraficasSencha::obtenModeloPorSeccion(MotorIMapaAPI::modelo::Seccion * seccion, bool incluirCampoLlave) {
	std::vector<std::string> camposInteres = servicioGeneradorInformacion.obtenCampos(seccion);
	std::string salida = servicioSerializadorInformacion.obtenCampos(camposInteres, incluirCampoLlave ? servicioGeneradorInformacion.campoLlave : "");
	return salida;
}

std::string MotorGraficasSencha::obtenDataStorePorSeccion(MotorIMapaAPI::modelo::Seccion * seccion) {
	std::map<MotorIMapaAPI::modelo::Seccion *, std::string>::iterator it = storePorSeccion.find(seccion);
	if(it != storePorSeccion.end())
		return it->second;

	std::string salida = servicioSerializadorInformacion.obtenStore(servicioGeneradorInformacion.obtenStore(seccion),
			servicioGeneradorInformacion.obtenCampos(seccion),
			servicioGeneradorInformacion.campoLlave);
	storePorSeccion[seccion] = salida;
	return salida;
}

}

