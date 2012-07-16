/*
 * ServicioSerializadorInformacion.h
 *
 *  Created on: 29/11/2011
 *      Author: LUIS.RANGEL
 */

#ifndef SERVICIOSERIALIZADORINFORMACION_H_
#define SERVICIOSERIALIZADORINFORMACION_H_

#include <string>
#include <vector>
#include <map>


namespace MotorGraficasSencha {

class ServicioSerializadorInformacion {
public:
	ServicioSerializadorInformacion();
	virtual ~ServicioSerializadorInformacion();

	std::string obtenCampos(std::vector<std::string> campos, const std::string campoLlave);
	std::string obtenStore(std::vector<std::map<std::string, std::string> > infoStore, std::vector<std::string> campos, const std::string campoLlave);
};

} /* namespace MotorGraficasSencha */
#endif /* SERVICIOSERIALIZADORINFORMACION_H_ */
