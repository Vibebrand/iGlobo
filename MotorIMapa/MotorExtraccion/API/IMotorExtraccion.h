#ifndef IMOTOREXTRACCION_H_
#define IMOTOREXTRACCION_H_

#include "IControladorSecciones.h"

namespace MotorExtraccion {

class IMotorExtraccion {
public:
	static IMotorExtraccion * instance();

	virtual void procesaArchivo(const char * archivo) = 0;
	virtual IControladorSecciones * obtenControladorSecciones() = 0;

protected:
	IMotorExtraccion() {}
	virtual ~IMotorExtraccion() {}

private:
	static IMotorExtraccion * _instance;
};

}

#endif //IMOTOREXTRACCION_H_
