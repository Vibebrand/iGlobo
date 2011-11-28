//
//  iControladorVista.h
//  iGlobo
//
//  Created by Jesus Cagide on 28/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol iControladorVista <NSObject>

-(UIView *) obtenerRepresentacionBajoMarco:(CGRect) tamanioVentana;
-(UIView *) obtenerRepresentacion;


@end
