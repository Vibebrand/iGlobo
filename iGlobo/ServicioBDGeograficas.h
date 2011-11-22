//
//  ServicioBDGeograficas.h
//  iGlobo
//
//  Created by Jesus Cagide on 18/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WhirlyGlobe/WhirlyGlobe.h>
//TODO crear protocolo de este servicio par el desacoplamiento
@interface ServicioBDGeograficas : NSObject
{
    NSDictionary *_countryDescription;
    NSDictionary *_oceanDescription;
    NSDictionary *_regionDescription;
    
    WhirlyGlobe::VectorDatabase *countryDb;
    WhirlyGlobe::VectorDatabase *oceanDb;
    WhirlyGlobe::VectorDatabase *regionDb;
}

-(void) llenarDiccionarios;

-(void) procesarBasesDeDatosVectoriales;

-(WhirlyGlobe::VectorDatabase *) obtenerBDPaises;

-(WhirlyGlobe::VectorDatabase *) obtenerBDOceanos;

-(WhirlyGlobe::VectorDatabase *) obtenerBDRegiones;


@property(nonatomic, retain) NSDictionary *countryDescription;
@property(nonatomic, retain) NSDictionary *oceanDescription;
@property(nonatomic, retain) NSDictionary *regionDescription;

@end
