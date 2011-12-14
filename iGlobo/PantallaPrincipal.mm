//
//  PantallaPrincipal.m
//  iGlobo
//
//  Created by Jesus Cagide on 24/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "PantallaPrincipal.h"

@implementation PantallaPrincipal

@synthesize representacionGlobo = _representacionGlobo;
@synthesize representacionGraficaBarrasIzquierdo = _representacionGraficaBarrasIzquierdo;
@synthesize representacionGraficaBarrasDerecha = _representacionGraficaBarrasDerecha;
@synthesize controladorVista = _controladorRepresentacionGlobo;
@synthesize controladorSencha;
@synthesize controladorSencha2;
@synthesize webView;
@synthesize webView2;

@synthesize controladorPiramidePoblacional = _controladorPiramidePoblacional;

-(void)dealloc
{
    [_representacionGlobo release];
    [_representacionGraficaBarrasIzquierdo release];
    [_controladorRepresentacionListaGraficaBarrasIzquierda release];
    
    
    [_representacionGraficaBarrasDerecha release];
    [_controladorRepresentacionListaGraficaBarrasDerecha release];
    
    [_controladorRepresentacionGlobo release];
    [_controladorPiramidePoblacional release];

    [self setControladorSencha: nil];
    [self setControladorSencha2: nil];
    
    [super dealloc];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.representacionGlobo.layer.cornerRadius = 5;

    _controladorRepresentacionListaGraficaBarrasIzquierda = [[ ControladorListaBarras alloc] initWithNibName:@"ControladorListaBarras" bundle:nil ];
    
     _controladorRepresentacionListaGraficaBarrasDerecha = [[ ControladorListaBarras alloc] initWithNibName:@"ControladorListaBarras" bundle:nil ];
    
    [_controladorPiramidePoblacional setControladorBarrasHombres:_controladorRepresentacionListaGraficaBarrasDerecha];
    [_controladorPiramidePoblacional setControladorBarrasMujeres:_controladorRepresentacionListaGraficaBarrasIzquierda];
    
    
    [[self representacionGlobo] addSubview: _controladorRepresentacionGlobo.obtenerRepresentacion ];

    [[self representacionGraficaBarrasIzquierdo] addSubview: _controladorRepresentacionListaGraficaBarrasIzquierda.obtenerRepresentacion];
    
    [[self representacionGraficaBarrasDerecha] addSubview: _controladorRepresentacionListaGraficaBarrasDerecha.obtenerRepresentacion];
    
    
    [_controladorRepresentacionListaGraficaBarrasDerecha establcerGenero:@"Hombres"];
    [_controladorRepresentacionListaGraficaBarrasIzquierda establcerGenero:@"Mujeres"];
    
    
    [[self webView] setOpaque:NO];
    [[self webView] setBackgroundColor:[UIColor clearColor]];
    
    [[self webView2] setOpaque:NO];
    [[self webView2] setBackgroundColor:[UIColor clearColor]];
    
    [[self controladorSencha] setWebView: [self webView]];
    [[self controladorSencha] viewDidLoad];

    [[self controladorSencha2] setWebView: [self webView2]];
    [[self controladorSencha2] viewDidLoad];
    
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	return YES;
}




@end
