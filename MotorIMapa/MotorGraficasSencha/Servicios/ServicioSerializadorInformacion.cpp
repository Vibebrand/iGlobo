/*
 * ServicioSerializadorInformacion.cpp
 *
 *  Created on: 29/11/2011
 *      Author: LUIS.RANGEL
 */

#include "../API/ServicioSerializadorInformacion.h"

#include <stdlib.h>
#include <iostream>
#include <sstream>

namespace MotorGraficasSencha {

ServicioSerializadorInformacion::ServicioSerializadorInformacion() {
}

ServicioSerializadorInformacion::~ServicioSerializadorInformacion() {
}

std::string ServicioSerializadorInformacion::obtenCampos(std::vector<std::string> campos, const std::string campoLlave) {
	std::stringstream salida;

	salida << "[";
	if(campoLlave != "") {
		salida << "'" << campoLlave << "'";
		if(static_cast<int>(campoLlave.size()) > 0) {
			salida << ", ";
		}
	}

	for(std::vector<std::string>::iterator it_campos = campos.begin(); it_campos != campos.end(); ++it_campos) {
		const std::string campo = static_cast<std::string>(*it_campos);
		if(campo != "") {
			salida << "'" << campo << "'";
			if(it_campos + 1 != campos.end()) {
				salida << ", ";
			}
		}
	}

	salida << "]";
	return salida.str();
}

std::string ServicioSerializadorInformacion::obtenStore(std::vector<std::map<std::string, std::string> > infoStore, std::vector<std::string> campos, std::string campoLlave) {
	std::stringstream salida;
	salida << "[";

	for(std::vector<std::map<std::string, std::string> >::iterator it_infoStore = infoStore.begin();
			it_infoStore != infoStore.end(); ++it_infoStore) {

		std::map<std::string, std::string> elementosInfoStore = static_cast<std::map<std::string, std::string> >(*it_infoStore);

		salida << "{";

		// Agregar valor de campoLlave
		if(campoLlave != "") {
			std::map<std::string, std::string>::iterator it_elementosInfoStore_campoLlave = elementosInfoStore.find(campoLlave);
			if(it_elementosInfoStore_campoLlave != elementosInfoStore.end()) {
				std::string valorInteres = static_cast<std::string>(it_elementosInfoStore_campoLlave->second);

				salida << "'" << campoLlave << "': " << "'" << valorInteres << "'";
				if(static_cast<int>(campos.size()) > 0) {
					salida << ", ";
				}
			} else {
				std::cerr << "Error: ServicioSerializadorInformacion::obtenStore " << campoLlave << " no definido en campos" << std::endl;
				exit(1);
			}
		}

		// Agregar valores restantes de Store
		for(std::vector<std::string>::iterator it_campos = campos.begin(); it_campos != campos.end(); ++it_campos) {
			std::string campoInteres = static_cast<std::string>(*it_campos);
			std::map<std::string, std::string>::iterator it_elementosInfoStore_campoInteres = elementosInfoStore.find(campoInteres);
			std::string valorInteres = "0";

			if(it_elementosInfoStore_campoInteres != elementosInfoStore.end()) {
				valorInteres = static_cast<std::string>(it_elementosInfoStore_campoInteres->second);
			}

			salida << "'" << campoInteres << "': " << valorInteres;
			if( it_campos + 1 != campos.end() ) {
				salida << ", ";
			}
		}

		salida << "}";
		if(it_infoStore + 1 != infoStore.end()) {
			salida << "," << std::endl;
		}
	}

	salida << "]";
	return salida.str();
}

} /* namespace MotorGraficasSencha */
