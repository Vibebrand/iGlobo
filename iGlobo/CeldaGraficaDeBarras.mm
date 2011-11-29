//
//  CeldaGraficaDeBarras.m
//  iGlobo
//
//  Created by Jesus Cagide on 29/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "CeldaGraficaDeBarras.h"

@implementation CeldaGraficaDeBarras

@synthesize rangoEdad = _rangoEdad;
@synthesize contenedorGraficaBarra = _contenedorGraficaBarra;


- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        [self agregarBarraAlaCelda];
    }
    return self;
}

-(void)agregarBarraAlaCelda
{
    //_representacionGraficaBarra = [[PDColoredProgressView alloc] initWithProgressViewStyle: UIProgressViewStyleDefault];
    if( _contenedorGraficaBarra )
    {
       // [_representacionGraficaBarra setFrame:[[self contenedorGraficaBarra] frame]];
        //[[self contenedorGraficaBarra] insertSubview:_representacionGraficaBarra atIndex:0];
        //[_representacionGraficaBarra setTintColor:[UIColor purpleColor]];
    }
}

-(void) dealloc
{
    [_rangoEdad release];
    [_contenedorGraficaBarra release];
    //[_representacionGraficaBarra release];
    [super dealloc];
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

}

-(void)establecerNombreCelda:(NSString*)nombre conValor:(float) valor
{
    [[self rangoEdad] setText:nombre];
    //[_representacionGraficaBarra setProgress:valor animated:TRUE];
}

@end
