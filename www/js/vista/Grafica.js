Grafo.Grafica = Ext.extend(Ext.chart.Chart,{
    titulo:"",
    initComponent : function() {
	this.on('activate', this.onGraficaActiva, this );
        this.on('afterrender', this.inicializaGrafica, this );
	Grafo.Grafica.superclass.initComponent.call(this);
    },
    onGraficaActiva :function(){ 
	Ext.dispatch({
	    controller:'ControladorGrafica',
	    action:'establecerGraficaActiva',
	    views: { graficaActiva : this}
	});
    },
    inicializaGrafica : function() {
        Ext.dispatch({
            controller: 'ControladorGrafica',
            action: 'inicializaGrafica',
            views: {grafica : this}
        });
    }
});
Ext.reg('grafica', Grafo.Grafica);