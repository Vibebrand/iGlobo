//
//  ControladorMapa.h
//  iGlobo
//
//  Created by Jesus Cagide on 17/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WhirlyGlobe/WhirlyGlobe.h>
#import "iDelegadoControladorMapa.h"
#import "ServicioBDGeograficas.h"
#import <list>

typedef std::set<WhirlyGlobe::SimpleIdentity> SimpleIDSet;
typedef enum {PoligonoPais ,PoligonoOceano} TipoPoligono;
static const unsigned int MaxRepresentacionesPoligono = 15;

class RepresentacionPoligono
{
public:
    RepresentacionPoligono(){};
    virtual ~RepresentacionPoligono(){};
    
    TipoPoligono tipoPoligono;
    WhirlyGlobe::ShapeSet frontera;
    WhirlyGlobe::SimpleIdentity idFrontera;
    WhirlyGlobe::SimpleIdentity idEtiqueta;
    float puntoMedio;
    WhirlyGlobe::ShapeSet subPoligonos;
    WhirlyGlobe::SimpleIdentity idSubPoligonos;
    WhirlyGlobe::SimpleIdentity subEtiquetas;
    //extrer referencia en un servicio adecuado
    //SimpleIDSet subPoligonosDibujados;
};

typedef std::list<RepresentacionPoligono*> RepresentacionesDePoligono;

@interface ControladorMapa : NSObject<iDelegadoControladorMapa>
{
    RepresentacionesDePoligono _poligonosDibujados;
#pragma Layers
    
    WhirlyGlobeLayerThread *_layerThread;
    WhirlyGlobe::GlobeScene * _scene;
    WhirlyGlobeView *_globeView;
    VectorLayer * _vectorLayer;
    LabelLayer * _labelLayer;
    float _maxEdgelen;
    
#pragma ServicioDeDatos
    ServicioBDGeograficas *_servicioBDGeograficas;
    
//Desacoplar a un servicio de Datos    
}

-(SingleLabel*) createLabelInfunction:(WhirlyGlobe::ShapeSet) shapes withMinWidth:(float)minWidth andName:(NSString*)name minVis:(float)minVis maxVis:(float)maxVis withConfig:(NSMutableDictionary *) labelDescription;

#pragma iControladorMapa

-(RepresentacionPoligono *) agregarOceano: (WhirlyGlobe::VectorArealRef) area;

-(RepresentacionPoligono *) agregarPais:(NSDictionary*) arDict;

-(void) agregarEstados:(RepresentacionPoligono*) poligono conPoligonos:(WhirlyGlobe::ShapeSet) regionShapes;

-(void)eliminarRepresentacionPoligono:(RepresentacionPoligono *) poligono;

-(void)calcLabelPlacement:(WhirlyGlobe::ShapeSet *)shapes loc:(WhirlyGlobe::GeoCoord &)loc  minWidth:(float)minWidth width:(float *)retWidth height:(float *)retHeight;

#pragma iDelegado Controlador Mapa

- (void)procesarBaseDeDatosVectorial;

-(void)cmdGeoReferenciaSeleccionada:(NSNotification *)notificacion;

-(WhirlyGlobeLayerThread *) obtenerlayerThread;

-(void)establecerlayerThread:(WhirlyGlobeLayerThread *) layerThread;

-(void)establecerScene:(WhirlyGlobe::GlobeScene *)scene;

#pragma Argumentos

@property(nonatomic,retain) WhirlyGlobeLayerThread *layerThread;
@property(nonatomic,retain) VectorLayer *vectorLayer;
@property(nonatomic,retain) LabelLayer *labelLayer;
@property(nonatomic,retain) WhirlyGlobeView *globeView;

@property(nonatomic, retain) ServicioBDGeograficas *servicioBDGeograficas;


@end
