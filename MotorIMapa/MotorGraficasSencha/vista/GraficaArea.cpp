/*
 * GraficaPie.cpp
 *
 *  Created on: 29/11/2011
 *      Author: LUIS.RANGEL
 */

#include "GraficaArea.h"

namespace MotorGraficasSencha {

GraficaArea::GraficaArea() {
	definicionGrafica = "{ \
				id : '$$id', \
				titulo: '$$tituloGrafica', \
				xtype: 'grafica', \
                store : Ext.StoreMgr.get('$$nombreStore'), \
                theme : 'iGlobe', \
                animate: true, \
                insetPadding : 10, \
                interactions:[{ type:'panzoom',gesture:'pinch'}],\
                legend : { \
				dock : true \
				}, \
                axes: [{ \
                    type: 'Numeric', \
                    position: 'left', \
                    grid: true, \
                    fields: $$regiones, \
                    minimum: 0, \
                    adjustMinimumByMajorUnit: 0, \
                    grid: true, \
                    label : { fill: '#FFF' }\
               	    },{ \
                    type: 'Category', \
                    grid: true, \
                    position: 'bottom', \
                    fields: ['$$campoLlave'], \
                    label : { fill: '#FFF' }\
                }], \
                series: [{ \
                    type: 'area', \
                    highlight: false, \
                    axis: 'left', \
                    xField: '$$campoLlave', \
                    yField: $$regiones \
                }] \
            }";
}

GraficaArea::~GraficaArea() {
}

std::string GraficaArea::obtenDefinicionGrafica() {
	return definicionGrafica;
}

void GraficaArea::actualizaDefinicion(std::string &salida, MotorIMapaAPI::modelo::Seccion * seccion, const std::string campoLlave, const std::string campoValor, const std::string campos, const std::string dataStore) {
	replace(salida, "$$regiones", campos);
	replace(salida, "$$campoLlave", campoLlave);
}

} /* namespace MotorGraficasSencha */
