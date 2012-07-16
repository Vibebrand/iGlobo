#ifndef GRAFICA_H
#define GRAFICA_H

#include <string>

#include "../../API/Seccion.h"

namespace MotorGraficasSencha {

class Grafica
{
public:
    Grafica();
    virtual ~Grafica();

	virtual std::string obtenInstruccionModelo(MotorIMapaAPI::modelo::Seccion * seccion, const std::string campos);
	virtual std::string obtenInstruccionStore(MotorIMapaAPI::modelo::Seccion * seccion, const std::string dataStore, bool actualizar);
	virtual std::string obtenInstruccionGrafica(MotorIMapaAPI::modelo::Seccion * seccion, const std::string campoLlave, const std::string campoValor, const std::string campos, const std::string dataStore);

protected:
	virtual std::string obtenDefinicionGrafica() = 0;
	virtual void actualizaDefinicion(std::string &definicionActual, MotorIMapaAPI::modelo::Seccion * seccion, const std::string campoLlave, const std::string campoValor, const std::string campos, const std::string dataStore) = 0;

	std::string obtenId(MotorIMapaAPI::modelo::Seccion * seccion);
	std::string obtenNombreModelo(MotorIMapaAPI::modelo::Seccion * seccion);
	std::string obtenNombreStore(MotorIMapaAPI::modelo::Seccion * seccion);


	// Ref: http://www.daniweb.com/software-development/cpp/threads/103759
	void replace(std::string &str, const std::string &find_what, const std::string &replace_with);
private:
};

}

#endif // GRAFICA_H
