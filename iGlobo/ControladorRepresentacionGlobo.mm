//
//  ControladorRepresentacionGlobo.m
//  iGlobo
//
//  Created by Jesus Cagide on 16/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ControladorRepresentacionGlobo.h"
#import "ServicioBDGeograficas.h"
#import "ServicioMosaicoGeografico.h"

#define CENTER_COORD1 512.0
#define CENTER_COORD2 384.0

@implementation ControladorRepresentacionGlobo

@synthesize glView;
@synthesize sceneRenderer;
@synthesize fpsLabel,drawLabel;
@synthesize pinchDelegate;
@synthesize swipeDelegate;
@synthesize rotateDelegate;
@synthesize panDelegate;
@synthesize tapDelegate;
@synthesize pressDelegate;
@synthesize theView;
@synthesize texGroup;
@synthesize layerThread;
@synthesize earthLayer;
@synthesize vectorLayer;
@synthesize labelLayer;
@synthesize controladorCapaDeInteraccion;

@synthesize loftlayer;

- (void)clear
{
	[[NSNotificationCenter defaultCenter] removeObserver:self];
    
    if (self.layerThread)
    {
        [self.layerThread cancel];
        while (!self.layerThread.isFinished)
            [NSThread sleepForTimeInterval:0.001];
    }
    
    [_panelRedondo release];
    
    self.glView = nil;
    self.sceneRenderer = nil;
    
    self.drawLabel = nil;
    self.pinchDelegate = nil;
    self.swipeDelegate = nil;
    self.rotateDelegate = nil;
    self.panDelegate = nil;
    self.tapDelegate = nil;
    self.pressDelegate = nil;
    
    if (theScene)
    {
        delete theScene;
        theScene = NULL;
    }
    self.theView = nil;
    self.texGroup = nil;
    
    self.layerThread = nil;
    self.earthLayer = nil;
    self.vectorLayer = nil;
    self.labelLayer = nil;
    self.controladorCapaDeInteraccion = nil;
    self.loftlayer = nil;
    
    [controladorMapa release];
    // self.interactLayer = nil;
    // self.capatInteraccion = nil;
    // self.loftLayer = nil;
}


- (void)dealloc 
{
    [self clear];
    [super dealloc];
}

-(id)initWithView:(UIView*)view
{
    self = [super init];
    if(self)
    {
        [self setView:view];
    }
    return self;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    _panelRedondo = [[PanelRedondo alloc] initWithFrame: self.view.bounds];
    
    // Set up an OpenGL ES view and renderer
	self.glView = [[[EAGLView alloc] init] autorelease];
	self.sceneRenderer = [[[SceneRendererES1 alloc] init] autorelease];
	glView.renderer = sceneRenderer;
	glView.frameInterval = 2;  // 60 fps
    
    [_panelRedondo insertSubview:glView atIndex:0];
	[self.view insertSubview:_panelRedondo atIndex:0];
    //self.view.backgroundColor = [UIColor blackColor];
    //self.view.opaque = YES;
	self.view.autoresizesSubviews = YES;
    
	glView.frame =   CGRectMake(_panelRedondo.frame.origin.x +10 , _panelRedondo.frame.origin.y +10, _panelRedondo.frame.size.width -20, _panelRedondo.frame.size.height -20);
    glView.backgroundColor = [UIColor clearColor];
    
    // Create the textures and geometry, but in the right GL context
	[sceneRenderer useContext];
	
	// Set up a texture group for the world texture
	self.texGroup = [[[TextureGroup alloc] initWithInfo:[[NSBundle mainBundle] pathForResource:@"big_wtb_info" ofType:@"plist"]] autorelease];
    
	// Need an empty scene and view
	theScene = new WhirlyGlobe::GlobeScene(4*texGroup.numX,4*texGroup.numY);
	self.theView = [[[WhirlyGlobeView alloc] init] autorelease];
	
	// Need a layer thread to manage the layers
	self.layerThread = [[[WhirlyGlobeLayerThread alloc] initWithScene:theScene] autorelease];
	
	// Earth layer on the bottom
	self.earthLayer = [[[SphericalEarthLayer alloc] initWithTexGroup:texGroup] autorelease];
	[self.layerThread addLayer:earthLayer];
    
	// Set up the vector layer where all our outlines will go
	self.vectorLayer = [[[VectorLayer alloc] init] autorelease];
	[self.layerThread addLayer:vectorLayer];
    
	// General purpose label layer.
	self.labelLayer = [[[LabelLayer alloc] init] autorelease];
	[self.layerThread addLayer:labelLayer];
    
    
    self.loftlayer = [[[LoftLayer alloc] init] autorelease];
    self.loftlayer.gridSize = [self.earthLayer smallestTesselation];
    self.loftlayer.useCache = YES;
    [self.layerThread addLayer:loftlayer];
    
    
    controladorMapa = [[ControladorMapa alloc] init];
    [controladorMapa setServicioBDGeograficas:[[ServicioBDGeograficas new] autorelease] ];
    
    
    ServicioMosaicoGeografico *servicio = [[ServicioMosaicoGeografico alloc] initWithLoftLayer:[self loftlayer]];
    
    [controladorMapa setServicioMosaicoGeografico:servicio];
    
    [servicio release];
    
    [controladorMapa setLayerThread:self.layerThread];
    [controladorMapa setGlobeView:self.theView];
    [controladorMapa setLabelLayer:self.labelLayer];
    [controladorMapa setVectorLayer:self.vectorLayer];
    
    controladorMapa.maxEdgelen = [self.earthLayer smallestTesselation]/10.0;
    
    self.controladorCapaDeInteraccion = [[[ControladorCapaDeInteraccion alloc] initWithMapDelegate:controladorMapa] autorelease];
  
    [self.layerThread addLayer:controladorCapaDeInteraccion];
    
    // Give the renderer what it needs
	sceneRenderer.scene = theScene;
	sceneRenderer.view = theView;
	
	// Wire up the gesture recognizers
	self.pinchDelegate = [WhirlyGlobePinchDelegate pinchDelegateForView:glView globeView:theView];
	self.panDelegate = [PanDelegateFixed panDelegateForView:glView globeView:theView];
	self.tapDelegate = [WhirlyGlobeTapDelegate tapDelegateForView:glView globeView:theView];
    self.pressDelegate = [WhirlyGlobeLongPressDelegate longPressDelegateForView:glView globeView:theView];
    self.rotateDelegate = [WhirlyGlobeRotateDelegate rotateDelegateForView:glView globeView:theView];
	
    
    // This will start loading things
	[self.layerThread start];
}

- (void)viewDidUnload
{
     [self clear];
    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated
{
	[self.glView startAnimation];
	
	[super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[self.glView stopAnimation];
	
	[super viewWillDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return YES;
}

- (void)lightingSetup:(SceneRendererES1 *)sceneRenderer
{
    const GLfloat			lightAmbient[] = {0.5, 0.5, 0.5, 1.0};
    const GLfloat			lightDiffuse[] = {0.6, 0.6, 0.6, 1.0};
    const GLfloat			matAmbient[] = {0.5, 0.5, 0.5, 1.0};
    const GLfloat			matDiffuse[] = {1.0, 1.0, 1.0, 1.0};	
    const GLfloat			matSpecular[] = {0.2, 0.2, 0.2, 1.0};
    const GLfloat			lightPosition[] = {0.75, 0.5, 1.0, 0.0}; 
    const GLfloat			lightShininess = 128.0;
    
    //Configure OpenGL lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, lightShininess);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); 
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
}

@end
