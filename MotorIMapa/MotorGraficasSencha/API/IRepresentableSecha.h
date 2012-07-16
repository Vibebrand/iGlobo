#ifndef _IREPRESENTABLESENCHA_H_
#define _IREPRESENTABLESENCHA_H_

#include <string>

namespace MotorGraficasSencha {

class IRepresentableSencha {
public:
	virtual ~IRepresentableSencha() {}
	virtual bool requiereInicializacion() = 0;
	virtual void vistaRequerida(bool requerida) = 0;
	virtual void ejecutaInstruccion(const std::string instruccion) = 0;
};

}

#endif
