function ControladorGraficaDelegado() {
}

ControladorGraficaDelegado.cargaInfo = function(info, graficaActiva, funcionInfoProcesada) {
    var infoProcesada = eval(info);
    if(infoProcesada !== null && infoProcesada !== undefined) {
        var infoInteres = ControladorGraficaDelegado.procesaInfo(infoProcesada, graficaActiva.store.data.map);
        funcionInfoProcesada(infoInteres["infoProcesada"]);
        NativeBridge.call("InfoGraficaDetalleActualizada",  [graficaActiva.titulo, infoInteres["informacionConcentrada"]], function() {});
    }
}

ControladorGraficaDelegado.procesaInfo = function(infoProcesada, series) {
    var identificador = undefined;
    var informacionConcentrada = {};
    var salida = []
    lista = []
    
    for (var nombreSerieInterno in series) {
        var mapaValores = series[nombreSerieInterno].data;
        lista.push(mapaValores);
        
        for( var propiedadRequerida in mapaValores) {
            if(propiedadRequerida.match(/^nombre/) !== null) {
                identificador = propiedadRequerida; // nombreNivel, nombreCiencia, etc...
                break;
            }
        }
    }
    
    if(identificador !== undefined)
        lista = lista.sort(function(a, b){
            var v1 = a[identificador].toLowerCase();
            var v2 = b[identificador].toLowerCase();
            if (v1 < v2) //sort string ascending
                return -1;
            if (v1 > v2)
                return 1;
            return 0; });

    var longitudMaximaLista = lista.length;
    for(contador = 0; contador < longitudMaximaLista; contador++) {
        mapaValores = lista[contador];
        var procesado = false;
        var elementoAProcesar = null;                              
        var identificadorElementoSerie = undefined;
        
        if(identificador !== undefined) {
            identificadorElementoSerie = mapaValores[identificador];
            
            // Buscar elemento a modificar en informacion procesada
            for(var i = 0; i < infoProcesada.length; i++) {
                var elementoInfoProcesada = infoProcesada[i];
                
                if((identificadorElementoSerie + '') === (elementoInfoProcesada[identificador] + '') ) {
                    elementoAProcesar = elementoInfoProcesada;
                    break;
                }
            }
        }
        
        // Agregar pojo nuevo en caso de no existir
        if(elementoAProcesar === null) {
            elementoAProcesar = {};
            if (identificador !== undefined) {
                elementoAProcesar[identificador] = identificadorElementoSerie;
            }
            infoProcesada[infoProcesada.length] = elementoAProcesar;
        }
        
        salida.push(elementoAProcesar);
        
        // Procesar elementos faltantes
        for(llaveNecesaria in mapaValores) {
            if(elementoAProcesar[llaveNecesaria] === undefined) {
                elementoAProcesar[llaveNecesaria] = 0;
            }
            
            if(llaveNecesaria !== identificador) {
                
                if(identificador === "nombreCiencia") {
                    informacionConcentrada[elementoAProcesar[identificador]] = elementoAProcesar["cantidad"];
                } else {
                    informacionConcentrada[llaveNecesaria] = informacionConcentrada[llaveNecesaria] === undefined ? 
                        elementoAProcesar[llaveNecesaria] : 
                        informacionConcentrada[llaveNecesaria] + elementoAProcesar[llaveNecesaria];
                }
            }
        }
    }
    
    return {
        "infoProcesada" : salida,
        "informacionConcentrada" : informacionConcentrada
    }
}
