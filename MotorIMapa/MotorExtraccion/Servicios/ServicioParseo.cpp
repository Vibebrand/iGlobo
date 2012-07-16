/*
 * ServicioParseo.cpp
 *
 *  Created on: 23/11/2011
 *      Author: LUIS.RANGEL
 */

#include "ServicioParseo.h"
#include "LectorXML.h"

#include "../../API/Seccion.h"

namespace MotorExtraccion {
namespace Servicios {

static ServicioParseo * elemento = NULL;
void callbackFunction(int tipo, int Depth, int NodeType, const char * name, int IsEmptyElement, int HasValue, int HasAttributes, const char * value);

void callbackFunction(int tipo, int Depth, int NodeType, const char * name, int IsEmptyElement, int HasValue, int HasAttributes, const char * value) {
	if(elemento != NULL)
	{
		ElementoLeido elementoInteres;
		elementoInteres.type = tipo == 0 ? ElementoLeido::ELEMENTO : ElementoLeido::ATRIBUTO;
		elementoInteres.depth = Depth;
		elementoInteres.nodeType = NodeType;
		elementoInteres.isEmptyElement = IsEmptyElement;
		elementoInteres.hasValue = HasValue;
		elementoInteres.hasAttributes = HasAttributes;
		elementoInteres.constName = name != NULL ? name : "";
		elementoInteres.constValue = value != NULL ? value : "";

		elemento->agregarElemento(elementoInteres);
	}
}

// TODO Inicializar y limpiar variables
ServicioParseo::ServicioParseo(const char * nombreArchivo, IServicioParseoDelegado * delegado) {
	this->delegado = delegado;

	estadoActual = ESPERA;
	elemento = this;
	estadoAgregarTipos = false;

	streamFile(nombreArchivo, callbackFunction);
}

ServicioParseo::~ServicioParseo() {
}

void ServicioParseo::llenarVariablesEnSeccionActual() {
	if(this->seccionActual) {
		for(std::vector<std::string>::iterator it = nombreConjuntos.begin(); it != nombreConjuntos.end(); ++it) {
			std::string nombreConjunto = static_cast<std::string>(*it);
			std::map<std::string, std::string> variableDeConjunto = variables[nombreConjunto];
			for(std::map<std::string, std::string>::iterator itVariables = variableDeConjunto.begin(); itVariables != variableDeConjunto.end(); ++itVariables) {
				seccionActual->variables[itVariables->first] = itVariables->second;
			}
		}
	}
}

void ServicioParseo::agregarElemento(ElementoLeido elementoLeido)
{
	if(elementoLeido.type == ElementoLeido::ELEMENTO) { // ELEMENTOS
		if(elementoLeido.constName == "conjunto") {
			if(elementoLeido.nodeType == 1) { // Nuevo conjunto
				estadoActual = AGREGANDO_CONJUNTO;
			} else if(elementoLeido.nodeType == 15) { // Conjunto finalizado
				//Liberar variables
				std::string nombreConjuntoInteres = nombreConjuntos.back();
				variables.erase(nombreConjuntoInteres);
				nombreConjuntos.pop_back();
			}
		} else if(elementoLeido.constName == "variables") {
			if(elementoLeido.nodeType == 1 && estadoActual == AGREGANDO_CONJUNTO) { // Nueva variable para conjunto
				estadoActual = AGREGANDO_CONJUNTO_VARIABLES;
			} else if(elementoLeido.nodeType == 15) { // Finalizado carga de variables para conjunto actual
				estadoActual = AGREGANDO_CONJUNTO;
			}
		} else if(elementoLeido.constName == "concepto") {
			if(elementoLeido.nodeType == 1) {
				estadoAgregarTipos = true;

				if(estadoActual == AGREGANDO_CONJUNTO_VARIABLES) { // Nuevo concepto para variables en conjunto actual
					estadoActual = AGREGANDO_CONJUNTO_VARIABLES_CONCEPTO;
				} else if(estadoActual == AGREGANDO_SECCION || estadoActual == AGREGANDO_SECCION_CONCEPTO) {

					MotorIMapaAPI::modelo::Concepto * nuevoConcepto = new MotorIMapaAPI::modelo::Concepto;

					if(conceptoActual == NULL) {
						seccionActual->conceptos.push_back(nuevoConcepto);
						nuevoConcepto->conceptoPredecesor = NULL;
					} else {
						conceptoActual->conceptos.push_back(nuevoConcepto);
						nuevoConcepto->conceptoPredecesor = conceptoActual;
					}

					conceptoActual = nuevoConcepto;
					estadoActual = AGREGANDO_SECCION_CONCEPTO;
				}
			} else if(elementoLeido.nodeType == 15) {
				estadoAgregarTipos = false;

				if(estadoActual == AGREGANDO_SECCION_CONCEPTO) {
					if(conceptoActual) {
						conceptoActual = conceptoActual->conceptoPredecesor;
					}
				}
			}
		} else if(elementoLeido.constName == "#text") {
			if(elementoLeido.nodeType == 3) {
				if(estadoActual == AGREGANDO_CONJUNTO_VARIABLES_CONCEPTO) { // Agregar concepto al diccionario de variables
					std::string nombreConjuntoInteres = nombreConjuntos.back();
					variables[nombreConjuntoInteres][nombreConceptoActual] = elementoLeido.constValue;
				} else if(estadoActual == AGREGANDO_SECCION_CONCEPTO) {
					if(conceptoActual != NULL) {
						MotorIMapaAPI::modelo::Valor valor;
						valor.nombre = "";
						valor.valor = elementoLeido.constValue;

						if(static_cast<int>(tiposValores.size()))
							valor.tipo = tiposValores.back();

						if(static_cast<int>(tiposConceptos.size()))
							conceptoActual->tipo = tiposConceptos.back();

						conceptoActual->valores.push_back(valor);
					}
				} else if(estadoActual == AGREGANDO_SECCION_CONCEPTO_VALOR) {
					if(conceptoActual != NULL) {
						 // Llenar valor y asignarlo a concepto actual
						MotorIMapaAPI::modelo::Valor valorNuevo;
						valorNuevo.nombre = nombreValorActual;
						valorNuevo.valor = elementoLeido.constValue;

						if(static_cast<int>(tiposValores.size()))
							valorNuevo.tipo = tiposValores.back();

						conceptoActual->valores.push_back(valorNuevo);
					}
				}
			}
		} else if(elementoLeido.constName == "seccion") {
			if(elementoLeido.nodeType == 1) {
				estadoActual = AGREGANDO_SECCION;
				seccionActual = new MotorIMapaAPI::modelo::Seccion;
				estadoAgregarTipos = true;

				// Agregar variables a seccion
				llenarVariablesEnSeccionActual();

				conceptoActual = NULL;
			} else if(elementoLeido.nodeType == 15) {
				estadoAgregarTipos = false;

				if(delegado) { // Publicar nueva seccion terminada
					delegado->nuevaSeccion(seccionActual);
				} else {
					delete seccionActual;
				}
				seccionActual = NULL;
			}
		} else if (elementoLeido.constName == "valor") {
			if(elementoLeido.nodeType == 1) {
				estadoAgregarTipos = true;

				if(estadoActual == AGREGANDO_SECCION_CONCEPTO) {
					estadoActual = AGREGANDO_SECCION_CONCEPTO_VALOR;
				}
			} else if(elementoLeido.nodeType == 15) {
				estadoAgregarTipos = false;

				if(estadoActual == AGREGANDO_SECCION_CONCEPTO_VALOR) {
					estadoActual = AGREGANDO_SECCION_CONCEPTO;
				}
			}
		}
	} else if(elementoLeido.type == ElementoLeido::ATRIBUTO) { // ATRIBUTOS
		if(elementoLeido.constName == "nombre") {
			if(estadoActual == AGREGANDO_CONJUNTO) { // Asignando nombre de conjunto actual
				nombreConjuntos.push_back(elementoLeido.constValue);
			} else if(estadoActual == AGREGANDO_CONJUNTO_VARIABLES_CONCEPTO) { // Asignando nombre de concepto para variable actual
				nombreConceptoActual = elementoLeido.constValue;
			} else if(estadoActual == AGREGANDO_SECCION) { // Asignando nombre a seccion actual
				seccionActual->nombre = elementoLeido.constValue;
			} else if(estadoActual == AGREGANDO_SECCION_CONCEPTO) { // Asignando nombre a concepto de seccion actual
				if(conceptoActual != NULL && conceptoActual->nombre == "")
				{
					conceptoActual->nombre = elementoLeido.constValue;
				}
			} else if(estadoActual == AGREGANDO_SECCION_CONCEPTO_VALOR) {
				nombreValorActual = elementoLeido.constValue;
			}
		} else if (elementoLeido.constName == "nota") {
			if(estadoActual == AGREGANDO_SECCION_CONCEPTO) { // Asignando nota a concepto de seccion actual
				if(conceptoActual != NULL) {
					conceptoActual->nota = elementoLeido.constValue;
				}
			}
		} else if (elementoLeido.constName == "tipo-valor") {
			if(estadoAgregarTipos) {
				tiposValores.push_back(elementoLeido.constValue);
			} else {
				tiposValores.pop_back();
			}
		} else if (elementoLeido.constName == "tipo-concepto") {
			if(estadoAgregarTipos) {
				tiposConceptos.push_back(elementoLeido.constValue);
			} else {
				tiposConceptos.pop_back();
			}
		}
	}
}

}
}
