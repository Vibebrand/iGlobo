//
//  iControlMaestro.h
//  iGlobo
//
//  Created by Jesus Cagide on 05/12/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol iControlMaestro <NSObject>

- (void) estableceVariable:(NSString *) nombre valor: (NSString *) valor;
- (void) actualizaSecciones;

@end
