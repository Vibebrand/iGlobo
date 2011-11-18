//
//  iDelegadoControladorMapa.h
//  iGlobo
//
//  Created by Jesus Cagide on 18/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol iDelegadoControladorMapa <NSObject>

-(void)cmdGeoReferenciaSeleccionada:(NSNotification *)notificacion;

@end
