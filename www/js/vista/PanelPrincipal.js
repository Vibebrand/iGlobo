Grafo.PanelPrincipal = Ext.extend(Ext.Panel,{
    layout : 'fit',
    initComponent : function() {
	var me = this;
	me.injectCodeToSeries();
	me.items = me.buildItems();
	Grafo.PanelPrincipal.superclass.initComponent.call(this);
    },
    injectCodeToSeries: function(){
	var me = this;
	var funcionShowAll = Ext.chart.series.Series.prototype.showAll;
	var funcionHideAll = Ext.chart.series.Series.prototype.hideAll;
	var funcionShowAllPie = Ext.chart.series.Pie.prototype.showAll;
	var funcionHideAllPie = Ext.chart.series.Pie.prototype.hideAll;
        var funcionShowAllArea = Ext.chart.series.Area.prototype.showAll;
        var funcionHideAllArea = Ext.chart.series.Area.prototype.hideAll;                         
        
	Ext.chart.series.Series.prototype.showAll = function() { funcionShowAll.apply(this); me.codeInjected('nivel', this.yField, this.seriesIsHidden); }
	Ext.chart.series.Series.prototype.hideAll = function() { funcionHideAll.apply(this); me.codeInjected('nivel', this.yField, this.seriesIsHidden); }
        
        Ext.chart.series.Area.prototype.showAll = function() {
            var oculto = this.__excludes[this._index];
            if (oculto === undefined)
                oculto = false;
            me.codeInjected("titulo", this.yField[this._index], !oculto);
            funcionShowAllArea.apply(this);
        }
        Ext.chart.series.Area.prototype.hideAll = function() {
            var oculto = this.__excludes[this._index];
            if (oculto === undefined)
                oculto = false;
            me.codeInjected("titulo", this.yField[this._index], !oculto);
            funcionHideAllArea.apply(this);
        }

	Ext.chart.series.Pie.prototype.showAll = function() {
	    var itemInteres = this.chart.store.data.items[this._index]
	    funcionShowAllPie.apply(this);
	    if(itemInteres !== undefined) {
		me.codeInjected('nombre', itemInteres.get(this.label.field), this.isExcluded(this._index) );
	    }
	}
	Ext.chart.series.Pie.prototype.hideAll = function() {
	    var itemInteres = this.chart.store.data.items[this._index]
	    funcionHideAllPie.apply(this);
	    if(itemInteres !== undefined) {
		me.codeInjected('nombre', itemInteres.get(this.label.field), this.isExcluded(this._index) );
	    } 
	}
        
    },
    codeInjected:function(_nombre, _valor, _oculto){
	Ext.dispatch({
	    controller: 'ControladorGrafica',
	    action: 'cambioEnLeyenda',
	    json:  { nombre : _nombre , valor : _valor, oculto: _oculto }
	}); 
    },
    buildItems: function(){
	return[
	    { 	xtype:'carrusel',
		activeItem : 1,
		items :[ this.buildPieChart(), this.buildRadarChart(),this.buildPieChartDegrees()]}
	];
    },
    buildRadarChart:function(){
	return graficaRadar;
    },
    buildPieChart: function(){
	return graficaPieCiencia;
    },
    buildPieChartDegrees: function(){
	return graficaArea;
    }
});

var graficaRadar = {
    id : '_graficaRadar',
    xtype: 'grafica',
    titulo: 'Niveles SNI',
    toolbar:{position: 'right'},
    insetPadding : 50,
    animate:true,
    interactions: [
	{
	    type: 'rotate',
	    gesture:'pinch'
	}
    ],
    legend : {
	dock : true
    },
    store : Ext.StoreMgr.get('TitulosBajoNivelesStore'),
    axes : [{
	type : 'Radial',
	position : 'radial',
	steps : 3,
	label : {
	    field: 'nombreTitulo'
	}
    }],
    series : [
        {
            type : 'radar',
            xField : 'nombreTitulo',
            yField : 'C',
            showInLegend : true,
            style : {opacity : 0.3},
            title: 'Nivel C'
        },
	{
	    type : 'radar',
	    xField : 'nombreTitulo',
	    yField : 'I',
	    showInLegend : true,
	    style : {opacity : 0.3},
	    title: 'Nivel I'
	},
	{
	    type : 'radar',
	    xField : 'nombreTitulo',
	    yField : 'II',
	    showInLegend : true,
	    style : {opacity : 0.3},
	    title: 'Nivel II'
	},
	{
	    type : 'radar',
	    xField : 'nombreTitulo',
	    yField : 'III',
	    showInLegend : true,
	    style : {opacity : 0.3},
	    title: 'Nivel III'
	}
    ]
};

var graficaPieCiencia = {
    id : '_graficaPieCiencia',
    titulo: 'Areas SNI',
    xtype : 'grafica',
    toolbar:{position: 'right'},
    animate : true,
    insetPadding : 30,
    store : Ext.StoreMgr.get('AreasSNIStore'),
    legend : {
	dock : true
    },
    interactions: [
	{
	    type: 'iteminfo',
	    panel:{
		dockedItems : [{dock : 'top', xtype: 'toolbar', title: 'Detalles'}]
	    },
	    listeners: {
		show: function(interaction, item, panel) {
		    panel.update(['<ul><li><b>' + item.storeItem.get('nombreCiencia') + '</b></li>', '<li><b>Cantidad: </b> ' + item.storeItem.get('cantidad') + '</li></ul>'].join(''));
		}
	    }
	}
    ],
    series : [{
	type: 'pie',
        angleField: 'cantidad',
        showInLegend: true,
        label: {
            field: 'nombreCiencia',
            display: 'none',
            contrast: true,
            font: '18px Arial'
        }
    }]
}

var graficaArea = {
    id : '_graficaAreaTitulos',
    titulo: 'Titulos',
    xtype: 'grafica',
    store : Ext.StoreMgr.get('NivelesSNIBajoTiTulosStore'),
    animate: true,
    insetPadding : 30,
    legend : {
	dock : true
    },
    axes: [{
        type: 'Numeric',
        position: 'left',
        grid: true,
        fields: ['Diplomado', 'Doctorado', 'Especialidad', 'Licenciatura', 'Maestria', 'Posdoctorado'],
        minimum: 0,
        adjustMinimumByMajorUnit: 0,
        grid: {
            odd: {
                opacity: 1,
                fill: '#ddd',
                stroke: '#bbb',
                'stroke-width': 1
            }
       	}
    },{
        type: 'Category',
        grid: true,
        position: 'bottom',
        fields: ['nombreNivel'],
        title: 'Niveles SNI'
    }],
    series: [{
        type: 'area',
        highlight: false,
        axis: 'left',
        xField: 'nombreNivel',
        yField: ['Diplomado', 'Doctorado', 'Especialidad', 'Licenciatura', 'Maestria', 'Posdoctorado']
    }]
}

