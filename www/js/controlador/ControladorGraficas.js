

Ext.regController('ControladorGrafica', {
    mostrarFiltroGrafica: function(opciones){
	var graficaActiva = this._graficaActiva;
	graficaActiva.legend.show();
    },
    cambioEnLeyenda: function(opciones){
	console.log(opciones.json);
	var graficaActiva = this._graficaActiva;
	var me = this;
	if(NativeBridge != undefined) {
	    var contador = 0; 
	    NativeBridge.call("serieActualizada", [opciones.json], function() {
		for(var nombreGraficaInteres in me.graficasRegistradas) {
                    var graficaInteres = me.graficasRegistradas[nombreGraficaInteres];
		    contador = contador + 1;
		    (function(graficaInteres, me) {
			NativeBridge.call("cargaInfoGrafica", [graficaInteres.titulo], function(infoGrafica) {
			    contador = contador - 1;

			    if(contador == 0) {
				NativeBridge.call("infoCargada", [], function(infoCargada) {});
			    }

                            ControladorGraficaDelegado.cargaInfo(infoGrafica, graficaInteres, function(infoProcesada) {
                                if(infoProcesada !== undefined) {
                                    // Guardar info en grafica
                                    me.infoGraficasRegistradas[graficaInteres.id] = infoProcesada;
                                }});
                        });
		    })(graficaInteres, me);
		}
	    });
	}
    },
    mostrarResuladosFiltro:function(opciones){},
    establecerGraficaActiva: function(opciones){
	var me = this;
	if(opciones.views !== undefined && opciones.views.graficaActiva !== undefined) 
	    me._graficaActiva = opciones.views.graficaActiva;

	var graficaInteres = me._graficaActiva;
	var infoInteres = me.infoGraficasRegistradas[graficaInteres.id];
	
	
	setTimeout(function() {
	    NativeBridge.call("graficaActiva", [graficaInteres.titulo], function(info) {
                
            });
	    //Cargar info de grafica
	    if(infoInteres === undefined) {
		NativeBridge.call("cargaInfoGrafica", [graficaInteres.titulo], function(infoGrafica) {
                    ControladorGraficaDelegado.cargaInfo(infoGrafica, graficaInteres, function(infoProcesada) {
                        if(infoProcesada !== undefined) {
                            // Guardar info en grafica
                            me.infoGraficasRegistradas[graficaInteres.id] = infoProcesada;
                            graficaInteres.store.loadData(infoProcesada);
                        }});
                });
	    } else {
		graficaInteres.store.loadData(infoInteres);
	    }
	    
	    
	} , 0);
    },
    inicializaGrafica: function(opciones) {
	var graficaInteres = opciones.views.grafica;
	if(this.graficasRegistradas === undefined) {
	    this.graficasRegistradas = {};
            this.infoGraficasRegistradas = {};
	}
	if(!(graficaInteres.id in this.graficasRegistradas)) {
            this.graficasRegistradas[graficaInteres.id] = graficaInteres;
	}
    },
    recargaGraficaActual: function(opciones) {
	var me = this;
	establecerGraficaActiva();
    }
});
