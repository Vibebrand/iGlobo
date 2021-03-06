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
#import "iServicioDeIluminacionPorRegion.h"
#import "iDelegadoPanelRepresentacionGlobo.h"
#import <list>


typedef std::set<WhirlyGlobe::SimpleIdentity> SimpleIDSet;
typedef enum {PoligonoPais ,PoligonoOceano} TipoPoligono;

static const unsigned int MaxRepresentacionesPoligono = 15;
#define RotateToCountry true

class RepresentacionPoligono
{
public:
    RepresentacionPoligono();
    virtual ~RepresentacionPoligono();
    
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
    
#pragma Servicios
    ServicioBDGeograficas *_servicioBDGeograficas;
    id<iServicioDeIluminacionPorRegion> _servicioIluminacion;
    id<iDelegadoPanelRepresentacionGlobo> _delegadoPanelRepresentacionGlobo;
    
    ControlMaestro *_controlMaestro;
    
//Desacoplar a un servicio de Datos    
}

-(void)rotarElMapaSegunCoordenadas:(TapMessage *) _msg;

-(SingleLabel*) createLabelInfunction:(WhirlyGlobe::ShapeSet) shapes withMinWidth:(float)minWidth andName:(NSString*)name minVis:(float)minVis maxVis:(float)maxVis withConfig:(NSMutableDictionary *) labelDescription;

#pragma iControladorMapa

-(RepresentacionPoligono *) agregarOceano: (WhirlyGlobe::VectorArealRef) area;

-(RepresentacionPoligono *) agregarPais:(NSDictionary*) arDict;

-(void) agregarEstados:(RepresentacionPoligono*) poligono conPoligonos:(WhirlyGlobe::ShapeSet) regionShapes;

-(void)eliminarRepresentacionPoligono:(RepresentacionPoligono *) poligono;

- (RepresentacionPoligono *)buscarRepresentacionPoligono:(const WhirlyGlobe::GeoCoord &)geoCoord height:(float)heightAboveGlobe whichShape:(WhirlyGlobe::VectorShapeRef *)whichShape;

-(void)calcLabelPlacement:(WhirlyGlobe::ShapeSet *)shapes loc:(WhirlyGlobe::GeoCoord &)loc  minWidth:(float)minWidth width:(float *)retWidth height:(float *)retHeight;

- (void)cmdAccionSobreAreaGeografica:(TapMessage *)msg;

#pragma iDelegado Controlador Mapa

- (void)procesarBaseDeDatosVectorial;

-(void)cmdGeoReferenciaSeleccionada:(NSNotification *)notificacion;

-(WhirlyGlobeLayerThread *) obtenerlayerThread;

-(void)establecerlayerThread:(WhirlyGlobeLayerThread *) layerThread;

-(void)establecerScene:(WhirlyGlobe::GlobeScene *)scene;

-(void)estableceControlMaestro:(ControlMaestro *) controlMaestro;

#pragma Argumentos

@property(nonatomic,retain) WhirlyGlobeLayerThread *layerThread;
@property(nonatomic,retain) VectorLayer *vectorLayer;
@property(nonatomic,retain) LabelLayer *labelLayer;
@property(nonatomic,retain) WhirlyGlobeView *globeView;
@property(nonatomic, assign) float maxEdgelen;

@property(nonatomic, retain) ServicioBDGeograficas *servicioBDGeograficas;
@property(nonatomic, retain) id<iServicioDeIluminacionPorRegion> servicioIluminacion;
@property(nonatomic, assign) id<iDelegadoPanelRepresentacionGlobo> delegadoPanelRepresentacionGlobo;
@property(nonatomic, assign) ControlMaestro * controlMaestro;

@end
