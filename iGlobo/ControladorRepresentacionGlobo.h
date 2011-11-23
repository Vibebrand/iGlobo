//
//  ControladorRepresentacionGlobo.h
//  iGlobo
//
//  Created by Jesus Cagide on 16/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WhirlyGlobe/WhirlyGlobe.h>
#import "PanDelegateFixed.h"
#import "ControladorMapa.h"
#import "ControladorCapaDeInteraccion.h"
#import "LoftLayer.h"
@interface ControladorRepresentacionGlobo : UIViewController
{
    EAGLView *glView;
	SceneRendererES1 *sceneRenderer;
    
    // Various interaction delegates when this view controller is up
	WhirlyGlobePinchDelegate *pinchDelegate;
	WhirlyGlobeSwipeDelegate *swipeDelegate;
	PanDelegateFixed *panDelegate;
	WhirlyGlobeTapDelegate *tapDelegate;
    WhirlyGlobeLongPressDelegate *pressDelegate;
    WhirlyGlobeRotateDelegate *rotateDelegate;
    
	// Scene, view, and associated data created when controller is up
	WhirlyGlobe::GlobeScene *theScene;
	WhirlyGlobeView *theView;
	TextureGroup *texGroup;
	
	// Thread used to control Whirly Globe layers
	WhirlyGlobeLayerThread *layerThread;
	
	// Data layers, readers, and loaders
	SphericalEarthLayer *earthLayer;
	VectorLayer *vectorLayer;
	LabelLayer *labelLayer;
    LoftLayer * loftlayer;
    
    
    ControladorCapaDeInteraccion * controladorCapaDeInteraccion;
    
    ControladorMapa * controladorMapa;
    
    
	//InteractionLayer *interactLayer;
    //CapaInteraccion * capaInteraccion;
    //LoftLayer * loftLayer;
}

- (void)lightingSetup:(SceneRendererES1 *)sceneRenderer;
- (void)clear;

@property (nonatomic,retain) EAGLView *glView;
@property (nonatomic,retain) SceneRendererES1 *sceneRenderer;
@property (nonatomic,retain) UILabel *fpsLabel,*drawLabel;
@property (nonatomic,retain) WhirlyGlobePinchDelegate *pinchDelegate;
@property (nonatomic,retain) WhirlyGlobeSwipeDelegate *swipeDelegate;
@property (nonatomic,retain) WhirlyGlobeRotateDelegate *rotateDelegate;
@property (nonatomic,retain) PanDelegateFixed *panDelegate;
@property (nonatomic,retain) WhirlyGlobeTapDelegate *tapDelegate;
@property (nonatomic,retain) WhirlyGlobeLongPressDelegate *pressDelegate;
@property (nonatomic,retain) WhirlyGlobeView *theView;
@property (nonatomic,retain) TextureGroup *texGroup;
@property (nonatomic,retain) WhirlyGlobeLayerThread *layerThread;
@property (nonatomic,retain) SphericalEarthLayer *earthLayer;
@property (nonatomic,retain) VectorLayer *vectorLayer;
@property (nonatomic,retain) LabelLayer *labelLayer;
@property (nonatomic,retain) ControladorCapaDeInteraccion * controladorCapaDeInteraccion;

@property (nonatomic,retain)  LoftLayer * loftlayer;



@end
