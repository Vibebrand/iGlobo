//
//  ControladorListaBarras.m
//  iGlobo
//
//  Created by Jesus Cagide on 29/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ControladorListaBarras.h"

@implementation ControladorListaBarras

@synthesize tablaDatos = _tablaDatos;
@synthesize porcentajeResultante = _porcentajeResultante;
@synthesize celdaBarras  = _celdaBarras;
@synthesize cellNib = _cellNib;
@synthesize etiquetaNumeroTotalPorGenero = _etiquetaNumeroTotalPorGenero;
@synthesize genero = _genero;
@synthesize imagen = _imagen;

-(void)dealloc
{
    [_tablaDatos release];
    //[_rangosDeEdad release];
       [_celdaBarras release];
    [_cellNib release];
    
    [_genero release];
    
    [_porcentajeResultante release];
    [_etiquetaNumeroTotalPorGenero release];
    [_imagen release];
    
    
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
    return 17;
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
    [celda establecerNombreCelda:@"35-89" conValor: 0.70f ];
    
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
	[tableView deselectRowAtIndexPath:indexPath animated:YES];
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

@end