#include "Grafica.h"

#include <sstream>

namespace MotorGraficasSencha {

Grafica::Grafica()
{
	//ctor
}

Grafica::~Grafica()
{
    //dtor
}

std::string Grafica::obtenInstruccionModelo(MotorIMapaAPI::modelo::Seccion * seccion, const std::string campos) {
	std::stringstream salida;

	salida << "Ext.regModel('" << obtenNombreModelo(seccion)  << "',{"
			<< "fields :" << campos
			<< "});";

	return salida.str();
}

std::string Grafica::obtenInstruccionStore(MotorIMapaAPI::modelo::Seccion * seccion, const std::string dataStore, bool actualizar) {
	std::stringstream salida;

	if(!actualizar) {
		salida << "Ext.regStore({"
				<< "model   : '" << obtenNombreModelo(seccion)  << "',"
				<< "storeId : '" << obtenNombreStore(seccion) << "',"
				<< "data : " << dataStore
				<< "});";
	} else {
		//Instruccion de actualizacion de Store
		salida << "Ext.dispatch({ controller: 'ControladorGrafica', "
					<< "action: "<< "'actualizaGrafica', "
					<< "identificadorGrafica: '" << obtenId(seccion) << "', "
					<< "definicionGrafica: " << dataStore
					<<"});";
	}

	return salida.str();
}

std::string Grafica::obtenInstruccionGrafica(MotorIMapaAPI::modelo::Seccion * seccion, const std::string campoLlave, const std::string campoValor, const std::string campos, const std::string dataStore) {
	std::stringstream salida;

	std::string definicion( obtenDefinicionGrafica() );
	replace(definicion, "$$id", obtenId(seccion));
	replace(definicion, "$$nombreStore", obtenNombreStore(seccion));
	replace(definicion, "$$tituloGrafica", seccion->nombre);

	actualizaDefinicion(definicion, seccion, campoLlave, campoValor, campos, dataStore);

	salida << "Ext.dispatch({ controller: 'ControladorGrafica', "
			<< "action: "<< "'registraGrafica', "
            << "identificadorGrafica: '" << obtenId(seccion) << "', "
			<< "definicionGrafica: " << definicion
			<<"});";

	return salida.str();
}

std::string Grafica::obtenId(MotorIMapaAPI::modelo::Seccion * seccion) {
	std::stringstream nombreId;
	nombreId << "Id_"
			<< seccion->nombre;
	std::string salida = nombreId.str();
	replace(salida, " ", "");
	return salida;
}

std::string Grafica::obtenNombreModelo(MotorIMapaAPI::modelo::Seccion * seccion) {
	std::stringstream nombreModelo;
	nombreModelo << "Model_" << seccion->nombre;
	std::string salida = nombreModelo.str();
	replace(salida, " ", "");
	return salida;
}

std::string Grafica::obtenNombreStore(MotorIMapaAPI::modelo::Seccion * seccion) {
	std::stringstream nombreStore;
	nombreStore << "Store_" << seccion->nombre;
	std::string salida = nombreStore.str();
	replace(salida, " ", "");
	return salida;
}

void Grafica::replace(std::string &str, const std::string &find_what, const std::string &replace_with) {
	std::string::size_type pos=0;
	while((pos=str.find(find_what, pos)) != std::string::npos)
	{
		str.erase(pos, find_what.length());
		str.insert(pos, replace_with);
		pos+=replace_with.length();
	}
}

}
