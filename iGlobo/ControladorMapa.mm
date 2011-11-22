//
//  ControladorMapa.m
//  iGlobo
//
//  Created by Jesus Cagide on 17/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ControladorMapa.h"

@implementation ControladorMapa

@synthesize layerThread = _layerThread;
@synthesize vectorLayer = _vectorLayer;
@synthesize labelLayer = _labelLayer;
@synthesize globeView = _globeView;
@synthesize servicioBDGeograficas = _servicioBDGeograficas;

-(void) dealloc
{
    self.layerThread = nil;
    self.globeView = nil;
    self.vectorLayer = nil;
    self.labelLayer = nil;
    
    if (_scene)  delete _scene;
    
    for(RepresentacionesDePoligono::iterator it = _poligonosDibujados.begin(); it != _poligonosDibujados.end(); ++it)
        delete (*it);
    [_servicioBDGeograficas release];
    [super dealloc];
}

-(SingleLabel*) createLabelInfunction:(WhirlyGlobe::ShapeSet) shapes withMinWidth:(float)minWidth andName:(NSString*)name minVis:(float)minVis maxVis:(float)maxVis withConfig:(NSMutableDictionary *) labelDescription
{
    WhirlyGlobe::GeoCoord location;
    [labelDescription setObject:[NSNumber numberWithFloat:minVis] forKey:@"minVis"];
    [labelDescription setObject:[NSNumber numberWithFloat:maxVis] forKey:@"maxVis"];
    
    SingleLabel *label = [[[SingleLabel alloc] init] autorelease];
    float labelWidth,labelHeight;
    [self calcLabelPlacement:&shapes loc:location minWidth:minWidth width:&labelWidth height:&labelHeight];
    
    if (location.lat() > 1.25 || location.lat() < -1.1)
        [labelDescription setObject:[UIColor grayColor] forKey:@"textColor"];
    
    [label setText:name];
    [label setLoc:location];
    [label setDesc:labelDescription];
    
    float testWidth=labelWidth,testHeight=0.0;
    [label calcWidth:&testWidth height:&testHeight defaultFont:[labelDescription objectForKey:@"font"]];
    
    [labelDescription setObject:[NSNumber numberWithDouble:labelWidth] forKey:@"width"];
    [labelDescription setObject:[NSNumber numberWithDouble:labelHeight] forKey:@"height"];
    return label;
}

#pragma iDelegado Controlador Mapa

-(WhirlyGlobeLayerThread *) obtenerlayerThread
{
    return _layerThread;
}
 
- (void)procesarBaseDeDatosVectorial
{
    [_servicioBDGeograficas procesarBasesDeDatosVectoriales];
}

-(void)establecerlayerThread:(WhirlyGlobeLayerThread *) layerThread
{
    [self setLayerThread:layerThread];
}

-(void)establecerScene:(WhirlyGlobe::GlobeScene *)scene
{
    _scene = scene;
}

-(void)cmdGeoReferenciaSeleccionada:(NSNotification *)notificacion
{

}

#pragma iControladorMapa

-(RepresentacionPoligono *) agregarOceano: (WhirlyGlobe::VectorArealRef) area
{
    RepresentacionPoligono * poligono = new RepresentacionPoligono();
    poligono->tipoPoligono = PoligonoOceano;
    
    area->subdivide(_maxEdgelen);
    poligono->frontera.insert(area);
    poligono->puntoMedio = 0.0;
    poligono->idFrontera = [[self vectorLayer] addVector:area  desc:[[[self servicioBDGeograficas] oceanDescription]  objectForKey:@"shape"]];
    
    NSString *nombre = [area->getAttrDict() objectForKey:@"Name"];
    if(nombre)
    {
        NSMutableDictionary *etiqueta = [NSMutableDictionary dictionaryWithDictionary:[[[self servicioBDGeograficas] oceanDescription] objectForKey:@"label"]];
        
        WhirlyGlobe::GeoCoord location;
        WhirlyGlobe::ShapeSet canShapes;
        
        canShapes.insert(area);
        float labelWidth, labelHeight;
        [self calcLabelPlacement:&poligono->frontera loc:location minWidth:0.3 width:&labelWidth height:&labelHeight];
        
        [etiqueta setObject:[NSNumber numberWithDouble:labelWidth] forKey:@"width"];
        
        [etiqueta setObject:[NSNumber numberWithDouble:labelHeight] forKey:@"height"];
        poligono->idEtiqueta = [[self labelLayer] addLabel:nombre loc: location desc:etiqueta];
        
    }
    return poligono;
}

-(RepresentacionPoligono *) agregarPais:(NSDictionary*) arDict
{
    RepresentacionPoligono *poligono = new RepresentacionPoligono();
    poligono->tipoPoligono = PoligonoPais;
    NSString* nombre = [arDict objectForKey:@"ADMIN"];
    WhirlyGlobe::UIntSet iDsFrontera;
    
    self.servicioBDGeograficas.obtenerBDPaises->getMatchingVectors([NSString stringWithFormat:@"ADMIN like '%@'",nombre ], poligono->frontera);
    
    
    NSMutableDictionary *descripcionDelPais = [NSMutableDictionary dictionaryWithDictionary:[[[self servicioBDGeograficas] countryDescription] objectForKey:@"shape"]];
    
    NSString *regionSeleccionada = [arDict objectForKey:@"ADM0_A3"];
    if(nombre)
    {
        WhirlyGlobe::ShapeSet regionShapes;
         self.servicioBDGeograficas.obtenerBDRegiones->getMatchingVectors([NSString stringWithFormat:@"ISO like '%@'",regionSeleccionada],regionShapes);

        if (regionShapes.empty())
            poligono->puntoMedio = 0.0;
        // Don't let the country outline disappear too quickly
        if (poligono->puntoMedio > 0.6)
            poligono->puntoMedio = 0.6;
        
        [descripcionDelPais setObject:[NSNumber numberWithFloat:poligono->puntoMedio] forKey:@"minVis"];
        [descripcionDelPais setObject:[NSNumber numberWithFloat:100.0] forKey:@"maxVis"];
        poligono->idFrontera = [[self vectorLayer] addVectors:&poligono->frontera desc:descripcionDelPais ];
        
        NSMutableDictionary *descripcionEtiqueta = [NSMutableDictionary dictionaryWithDictionary:[descripcionDelPais objectForKey:@"label"]];
        
        SingleLabel *etiquetaPais =[self createLabelInfunction:poligono->frontera withMinWidth:0.3 andName:nombre minVis:poligono->puntoMedio maxVis:100.0 withConfig:descripcionEtiqueta];
        
        poligono->idEtiqueta = [ [self labelLayer] addLabel:etiquetaPais ];
        
        [self agregarEstados:poligono conPoligonos:regionShapes];
        
    }else
    {
        [descripcionDelPais setObject:[NSNumber numberWithFloat:0.0] forKey:@"minVis"];
        [descripcionDelPais setObject:[NSNumber numberWithFloat:100.0] forKey:@"maxVis"];
        poligono->idFrontera = [[self vectorLayer] addVectors:&poligono->frontera desc:descripcionDelPais];    
    }
    return poligono;
}

-(void) agregarEstados:(RepresentacionPoligono*) poligono conPoligonos:(WhirlyGlobe::ShapeSet) regionShapes
{
    NSMutableDictionary *regionShapeDescription = [NSMutableDictionary dictionaryWithDictionary:[[[self servicioBDGeograficas] regionDescription] objectForKey:@"shape"]];
    
    [regionShapeDescription setObject:[NSNumber numberWithFloat:0.0] forKey:@"minVis"];
    
    [regionShapeDescription setObject:[NSNumber numberWithFloat:poligono->puntoMedio] forKey:@"maxVis"];
    
    poligono->idSubPoligonos = [[self vectorLayer] addVectors:&regionShapes desc:regionShapeDescription];
    
    poligono->subPoligonos= regionShapes;
    
    NSMutableDictionary *regionLabelDescription = [NSMutableDictionary dictionaryWithDictionary:[[[self servicioBDGeograficas] regionDescription] objectForKey:@"label"]];
    
    [regionLabelDescription setObject:[NSNumber numberWithFloat:0.0] forKey:@"minVis"];
    
    [regionLabelDescription setObject:[NSNumber numberWithFloat:poligono->puntoMedio] forKey:@"maxVis"];
    
    NSMutableArray *etiquetas = [[[NSMutableArray alloc] init] autorelease];
    
    for(WhirlyGlobe::ShapeSet::iterator _iterator = regionShapes.begin();
        _iterator != regionShapes.end(); ++_iterator)
    {
        NSString* regionName =  [(*_iterator)->getAttrDict() objectForKey:@"NAME_1"];
        
        if(regionName)
        {
            WhirlyGlobe::GeoCoord regionLoc;
            SingleLabel *sLabel = [[[SingleLabel alloc] init] autorelease];
            NSMutableDictionary *thisDesc = [NSMutableDictionary dictionary];
            WhirlyGlobe::ShapeSet *canShapes = new WhirlyGlobe::ShapeSet;
            canShapes->insert(*_iterator);
            //printf("%p", canShapes);
            
            // SingleLabel *label = [self createLabelInfunction:canShapes withMinWidth:0.005 andName:regionName minVis:0.0 maxVis:poligono->puntoMedio withConfig:regionLabelDescription];
            float thisWidth,thisHeight;
            [self calcLabelPlacement: canShapes loc:regionLoc minWidth:0.004 width:&thisWidth height:&thisHeight];
            [sLabel setLoc: regionLoc];
            sLabel.text = regionName;
            sLabel.desc = thisDesc;
            
            // Max out the height of these labels
            float testWidth=thisWidth,testHeight=0.0;
            [sLabel calcWidth:&testWidth height:&testHeight defaultFont:[regionLabelDescription objectForKey:@"font"]];
            
            [thisDesc setObject:[NSNumber numberWithDouble:thisWidth] forKey:@"width"];
            [thisDesc setObject:[NSNumber numberWithDouble:thisHeight] forKey:@"height"];
            [etiquetas addObject:sLabel];
            
            //[self colorearSubPoligono: canShapes dePoligonoPadre:poligono];
            delete canShapes;
        }
    }
    if ([etiquetas  count] > 0)
        poligono->subEtiquetas = [[self labelLayer] addLabels:etiquetas desc:regionLabelDescription];
}

-(void)eliminarRepresentacionPoligono:(RepresentacionPoligono *) poligono
{
    RepresentacionesDePoligono::iterator it = std::find(_poligonosDibujados.begin(), _poligonosDibujados.end(), poligono);
    
    if( it != _poligonosDibujados.end())
    {
        [[self vectorLayer] removeVector:poligono->idFrontera];
        [[self vectorLayer] removeVector:poligono->idSubPoligonos];
        if(poligono->idEtiqueta)
            [[self labelLayer] removeLabel:poligono->idEtiqueta];
        [[self labelLayer] removeLabel:poligono->subEtiquetas];
        
        _poligonosDibujados.erase(it);
        delete poligono;
    }
}

-(void)calcLabelPlacement:(WhirlyGlobe::ShapeSet *)shapes loc:(WhirlyGlobe::GeoCoord &)loc  minWidth:(float)minWidth width:(float *)retWidth height:(float *)retHeight
{
    double width=0.0,height=0.0;    
    WhirlyGlobe::VectorRing *largeLoop = NULL;
    float largeArea = 0.0;
    
    // Work through all the areals that make up the country
    // We get disconnected loops (think Alaska)
    for (WhirlyGlobe::ShapeSet::iterator it = shapes->begin();
         it != shapes->end(); it++)
    {        
        WhirlyGlobe::VectorArealRef theAreal = boost::dynamic_pointer_cast<WhirlyGlobe::VectorAreal> (*it);
        if (theAreal.get() && !theAreal->loops.empty())
        {
            // We need to find the largest loop.
            // It's there that we want to place the label
            for (unsigned int ii=0;ii<theAreal->loops.size();ii++)
            {
                WhirlyGlobe::VectorRing *thisLoop = &(theAreal->loops[ii]);
                float thisArea = WhirlyGlobe::GeoMbr(*thisLoop).area();
                if (!largeLoop || (thisArea > largeArea))
                {
                    largeArea = thisArea;
                    largeLoop = thisLoop;
                }
            }
            
        }
    }
    // Now get a width in the direction we care about
    if (largeLoop)
    {
        WhirlyGlobe::GeoMbr ringMbr(*largeLoop);
        Point3f pt0 = PointFromGeo(ringMbr.ll());
        Point3f pt1 = PointFromGeo(ringMbr.lr());
        width = (pt1-pt0).norm() * 0.5;
        // Don't let the width get too crazy
        width = std::min(width,0.5);
        loc = ringMbr.mid();
        if (width < 1e-5)
            width = minWidth;
    } else
        height = 0.02;
    
    if (retWidth)
        *retWidth = width;
    if (retHeight)
        *retHeight = height;
}

@end
