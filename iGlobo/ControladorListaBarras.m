//
//  ControladorListaBarras.m
//  iGlobo
//
//  Created by Jesus Cagide on 29/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ControladorListaBarras.h"
#import "indicadorGraficaBarra.h"
@implementation ControladorListaBarras

@synthesize tablaDatos = _tablaDatos;
@synthesize porcentajeResultante = _porcentajeResultante;
@synthesize celdaBarras  = _celdaBarras;
@synthesize cellNib = _cellNib;
@synthesize etiquetaNumeroTotalPorGenero = _etiquetaNumeroTotalPorGenero;
@synthesize genero = _genero;
@synthesize imagen = _imagen;
@synthesize rangosDeEdad = _rangosDeEdad;
@synthesize currentPopTipViewTarget;

@synthesize etiquetaReferenciaPopOver;

-(void)dealloc
{
    [_tablaDatos release];
    [_celdaBarras release];
    [_cellNib release];
    
    [_genero release];
    
    [_porcentajeResultante release];
    [_etiquetaNumeroTotalPorGenero release];
    [_imagen release];
    
    self.currentPopTipViewTarget = nil;
    self.etiquetaReferenciaPopOver=nil;
    
    [super dealloc];
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.currentPopTipViewTarget = nil;
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

-(void) actualizarGrafica:(NSArray *) indicadoresGrafica
{
    [self setRangosDeEdad:indicadoresGrafica];
    [[self tablaDatos] reloadData];
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.cellNib = [UINib nibWithNibName:@"CeldagraficaBarras" bundle:nil];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
   
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	return YES;
}


#pragma mark -
#pragma mark Table view datasource methods


-(NSInteger) numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

-(NSInteger) tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section
{
    if(_rangosDeEdad)
        return [_rangosDeEdad count];
    return  0;
}

-(UITableViewCell *) tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString * identificador = @"RangosDeEdad";
    CeldaGraficaDeBarras *celda;
    
    
    
    celda = (CeldaGraficaDeBarras *)[tableView dequeueReusableCellWithIdentifier:identificador];
            
    if (celda == nil) {
        [self.cellNib  instantiateWithOwner:self options:nil];
        celda = [self celdaBarras];
        [celda agregarBarraAlaCelda];
        self.celdaBarras = nil;
    }
    
    if(_rangosDeEdad)
    {
        indicadorGraficaBarra *indicador = [_rangosDeEdad objectAtIndex: [indexPath row]  ];
        [celda establecerNombreCelda: [indicador nombreEtiqueta] conValor: [indicador porcentajeARepresentar]];
        
        [[self currentPopTipViewTarget] dismissAnimated:YES];
        self.currentPopTipViewTarget = nil;
    }
   
    return celda;
}

-(CGFloat) tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 11;
}

#pragma mark -
#pragma mark Table view delegate methods

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
	return @"";
}

-(void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
	[[self currentPopTipViewTarget] dismissAnimated:YES];
    self.currentPopTipViewTarget = nil;
    
    indicadorGraficaBarra *indicador = [_rangosDeEdad objectAtIndex: [indexPath row] ];
    NSString * mensaje = [NSString stringWithFormat:@" %.0f Mil personas que representa %.1f%% de la población de %@ ", indicador.valor, indicador.porcentajeSegunValor, self.genero];
    
    
     CMPopTipView * _popTipView = [[[CMPopTipView alloc] initWithMessage:mensaje ]autorelease];
    _popTipView.delegate = self;
    _popTipView.backgroundColor = [UIColor blackColor];
    _popTipView.textColor = [UIColor whiteColor];
    _popTipView.animation = arc4random() % 2;
    self.currentPopTipViewTarget = _popTipView;
   
    [_popTipView presentPointingAtView:self.etiquetaReferenciaPopOver inView:self.view animated:YES];
    //[tableView deselectRowAtIndexPath:indexPath animated:YES];
}

#pragma mark -
#pragma mark iControladorVista

-(UIView *) obtenerRepresentacionBajoMarco:(CGRect) tamanioVentana
{
    return [self view];
}
-(UIView *) obtenerRepresentacion
{
    return [self view];
}


-(void) establcerGenero:(NSString*)genero
{
    [self setGenero: genero];
    if([[self genero] length] > 0 )
    {
        [[self imagen] setImage:[UIImage imageNamed:[NSString stringWithFormat: @"%@.png",[self genero] ]  ]];
    }
}

-(void) establecerPorcentajeDeLaPoblacion:(NSString*) porcentajePoblacion enBaseAlaSumatoriaTotal:(NSString*)sumatorialTotal
{
    [[self porcentajeResultante] setText:porcentajePoblacion];
    [[self etiquetaNumeroTotalPorGenero] setText: [NSString stringWithFormat:@"%@ %@", sumatorialTotal, [self genero]]];
}

#pragma CMPopTipView

- (void)popTipViewWasDismissedByUser:(CMPopTipView *)popTipView
{
    self.currentPopTipViewTarget = nil;
}
@end