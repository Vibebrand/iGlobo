/*
 * Main.cpp
 *
 *  Created on: 01/12/2011
 *      Author: LUIS.RANGEL
 */

#ifdef MOTORIMAPA_BIN

#include "MotorIMapa.h"
#include "MotorGraficasSencha/MotorSencha.h"

#include <iostream>

class RepresentableMock;
void generaReporte(std::string entidad, MotorIMapa &motor, RepresentableMock &representableMock, bool inicializar = false);

class RepresentableMock : public MotorGraficasSencha::IRepresentableSencha {
public:
    RepresentableMock() : inicializar(true) {}
    
    // IRepresentableSencha
    bool requiereInicializacion();
	void vistaRequerida(bool requerida);
	void ejecutaInstruccion(std::string instruccion);
    
    bool inicializar;
};

bool RepresentableMock::requiereInicializacion() {
    return inicializar;
}

void RepresentableMock::vistaRequerida(bool requerida) {
    std::clog << "Vista requerida:" << requerida << std::endl;
}

void RepresentableMock::ejecutaInstruccion(const std::string instruccion) {
    std::clog << "Ejecuta instruccion: " << instruccion << std::endl;
}

void generaReporte(std::string entidad, MotorIMapa &motor, RepresentableMock &representableMock, bool inicializar) {
	std::clog << "---------------------------------------------------------------" << std::endl;
	std::clog << "Establecida Entidad federativa: " << entidad << std::endl;
	motor.estableceCambioVariable("Entidad federativa", entidad);
	if(inicializar) {
		std::clog << "Solicitar actualizacion, requerida inicializacion" << std::endl;
		representableMock.inicializar = true;
		motor.actualizaSecciones();
	}
	std::clog << "Solicitar actualizacion, evitar inicializacion" << std::endl;
	representableMock.inicializar = false;
	motor.actualizaSecciones();
	std::clog << "---------------------------------------------------------------" << std::endl;
}

int main(int argc, char ** argv) {
	MotorIMapa motor;
	motor.procesaArchivo(argv[1]);
    
    MotorGraficasSencha::MotorGraficasSencha motorSencha;
	RepresentableMock representableMock;
    motorSencha.registraRepresentable(&representableMock, "Poblacion de 12 agnos y mas", MotorGraficasSencha::MotorGraficasSencha::Area);
    motor.registraGestorSecciones(&motorSencha);

    generaReporte("", motor, representableMock, true);
    generaReporte("Nayarit", motor, representableMock, true);

	return 0;
}

#endif
