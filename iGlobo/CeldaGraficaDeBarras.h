//
//  CeldaGraficaDeBarras.h
//  iGlobo
//
//  Created by Jesus Cagide on 29/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PDColoredProgressView.h"

@interface CeldaGraficaDeBarras : UITableViewCell
{
    UILabel *_rangoEdad;
    UIView  *_contenedorGraficaBarra;
    //PDColoredProgressView *_representacionGraficaBarra;
}

@property(nonatomic, retain) IBOutlet UILabel * rangoEdad;
@property(nonatomic, retain) IBOutlet UIView * contenedorGraficaBarra;

-(void)agregarBarraAlaCelda;
-(void)establecerNombreCelda:(NSString*)nombre conValor:(float) valor;

@end
