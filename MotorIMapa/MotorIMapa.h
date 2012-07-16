/*
 * MotorIMapa.h
 *
 *  Created on: 30/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef MOTORIMAPA_H_
#define MOTORIMAPA_H_

#include <map>
#include <set>
#include <string>

#include "API/IMotorIMapa.h"
#include "API/IGestorSecciones.h"

#include "MotorExtraccion/API/IMotorExtraccion.h"
#include "MotorExtraccion/API/IControladorSeccionesDelegado.h"

class MotorIMapa : public MotorIMapaAPI::IMotorIMapa, public MotorExtraccion::IControladorSeccionesDelegado {
public:
	MotorIMapa();
    ~MotorIMapa();

	// MotorMapa::IMotorIMapa
	void registraGestorSecciones(MotorIMapaAPI::IGestorSecciones * gestorSecciones);
	void procesaArchivo(const char * rutaArchivo);
	void estableceCambioVariable(std::string nombre, std::string valor);
	void actualizaSecciones();

	// MotorExtraccion::IControladorSeccionesDelegado
	void seccionValida(MotorIMapaAPI::modelo::Seccion * seccion);
	void seccionInvalida(MotorIMapaAPI::modelo::Seccion * seccion);

private:
	MotorExtraccion::IMotorExtraccion * motorExtraccion;
	std::set<MotorIMapaAPI::IGestorSecciones *> gestoresRegistrados;
	std::map<std::string, std::set<MotorIMapaAPI::IGestorSecciones *> > gestoresSecciones;
};

#endif /* MOTORIMAPA_H_ */
