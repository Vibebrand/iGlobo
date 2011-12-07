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
    buildItems: function() {
	return[
	    {
		xtype:'carrusel',
		id: "xxx",
		items: [
		    {
			xtype: "panel"
		    }, {
			xtype: "panel"
		    }
		]
	    }
	];
    }
});