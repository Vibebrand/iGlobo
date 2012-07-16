/*
 * GraficaPie.cpp
 *
 *  Created on: 29/11/2011
 *      Author: LUIS.RANGEL
 */

#include "GraficaPie.h"

namespace MotorGraficasSencha {

    GraficaPie::GraficaPie() {
        definicionGrafica = "{\
        id : '$$id',\
        titulo: '$$tituloGrafica',\
        xtype : 'grafica',\
        theme : 'iGlobe', \
        toolbar:{position: 'right'},\
        animate : true,\
        insetPadding : 5,\
        store : Ext.StoreMgr.get('$$nombreStore'),\
        legend : {\
        dock : true\
        },\
        interactions: [\
        {\
	    type: 'iteminfo',\
	    panel:{\
		dockedItems : [{dock : 'top', xtype: 'toolbar', title: '$$tituloDockedItem'}]\
	    },\
	    listeners: {\
		show: function(interaction, item, panel) {\
        window.panelDeDetalle = panel; \
        panel.update(['<ul><li><b>' + item.storeItem.get('$$tituloAngleField') + '</b></li>', '<li><b>$$nombreAngleField: </b> ' + item.storeItem.get('$$angleField') + '</li></ul>'].join(''));\
		}\
	    }\
        }\
        ],\
        series : [{\
        type: 'pie',\
        angleField: '$$angleField',\
        showInLegend: true,\
        label: {\
        field: '$$tituloAngleField',\
        display: 'none',\
        contrast: true,\
        font: '18px Arial'\
        }\
        }]\
        }";
    }

GraficaPie::~GraficaPie() {
}

std::string GraficaPie::obtenDefinicionGrafica() {
	return definicionGrafica;
}

void GraficaPie::actualizaDefinicion(std::string &salida, MotorIMapaAPI::modelo::Seccion * seccion, const std::string campoLlave, const std::string campoValor, const std::string campos, const std::string dataStore) {
	replace(salida, "$$tituloAngleField", campoLlave);
	replace(salida, "$$nombreAngleField", campoValor);
	replace(salida, "$$angleField", campoValor);
	replace(salida, "$$tituloDockedItem", "Detalles");
}

} /* namespace MotorGraficasSencha */
