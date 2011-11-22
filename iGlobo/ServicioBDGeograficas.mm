//
//  ServicioBDGeograficas.m
//  iGlobo
//
//  Created by Jesus Cagide on 18/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ServicioBDGeograficas.h"

@implementation ServicioBDGeograficas
#pragma Synthesize

@synthesize countryDescription= _countryDescription;
@synthesize oceanDescription= _oceanDescription;
@synthesize regionDescription = _regionDescription;

-(id)init
{
    if (self) 
    {
        [self llenarDiccionarios];
    }
    return self;
}

-(void)dealloc
{
    self.countryDescription = nil;
    self.oceanDescription = nil;
    self.regionDescription= nil;
    if (countryDb)  delete countryDb;
    if (oceanDb)  delete oceanDb;
    if (regionDb)  delete regionDb;
    [super dealloc];
}

-(void) llenarDiccionarios
{
    NSString* countryShape= [[NSBundle mainBundle] pathForResource:@"10m_admin_0_map_subunits" ofType:@"shp"];
    NSString* oceanShape=[[NSBundle mainBundle] pathForResource:@"10m_geography_marine_polys" ofType:@"shp"];
    NSString* regionShape= [[NSBundle mainBundle] pathForResource:@"10m_admin_1_states_provinces_shp" ofType:@"shp"];
    
    // Visual representation for countries when they first appear
    self.countryDescription = [NSDictionary dictionaryWithObjectsAndKeys:
                               [NSDictionary dictionaryWithObjectsAndKeys:
                                [NSNumber numberWithBool:YES],@"enable",
                                [NSNumber numberWithInt:3],@"drawOffset",
                                [UIColor whiteColor],@"color",
                                nil],@"shape",
                               [NSDictionary dictionaryWithObjectsAndKeys:
                                [NSNumber numberWithBool:YES],@"enable",
                                [UIColor clearColor],@"backgroundColor",
                                [UIColor whiteColor],@"textColor",
                                [UIFont boldSystemFontOfSize:32.0],@"font",
                                [NSNumber numberWithInt:4],@"drawOffset",
                                nil],@"label",
                               nil];
    // Visual representation for oceans
    self.oceanDescription = [NSDictionary
                             dictionaryWithObjectsAndKeys:
                             [NSDictionary dictionaryWithObjectsAndKeys:
                              [NSNumber numberWithBool:YES],@"enable",
                              [NSNumber numberWithInt:2],@"drawOffset",
                              [UIColor colorWithRed:0.75 green:0.75 blue:1.0 alpha:1.0],@"color",
                              nil],@"shape",                          
                             [NSDictionary dictionaryWithObjectsAndKeys:
                              [NSNumber numberWithBool:YES],@"enable",
                              [UIColor colorWithRed:0.75 green:0.75 blue:1.0 alpha:1.0],@"textColor",
                              [NSNumber numberWithInt:4],@"drawOffset",
                              nil],@"label",
                             nil];
    // Visual representation of regions and their labels
    self.regionDescription = [NSDictionary dictionaryWithObjectsAndKeys:
                              [NSDictionary dictionaryWithObjectsAndKeys:
                               [NSNumber numberWithBool:YES],@"enable",
                               [NSNumber numberWithInt:1],@"drawOffset",
                               [UIColor grayColor],@"color",
                               nil],@"shape",
                              [NSDictionary dictionaryWithObjectsAndKeys:
                               [NSNumber numberWithBool:YES],@"enable",
                               [UIColor colorWithRed:0.8 green:0.8 blue:0.8 alpha:1.0],@"textColor",
                               [UIFont systemFontOfSize:32.0],@"font",
                               [NSNumber numberWithInt:2],@"drawOffset",
                               nil],@"label",
                              nil];

    
    NSString *docDir = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
    NSString *bundleDir = [[NSBundle mainBundle] resourcePath];
    
    // The country DB we want in memory to speed up taps
    countryDb = new WhirlyGlobe::VectorDatabase(bundleDir,docDir,@"countries",new WhirlyGlobe::ShapeReader(countryShape),NULL);
    oceanDb = new WhirlyGlobe::VectorDatabase(bundleDir,docDir,@"oceans",new WhirlyGlobe::ShapeReader(oceanShape),NULL);
    regionDb = new WhirlyGlobe::VectorDatabase(bundleDir,docDir,@"regions",new WhirlyGlobe::ShapeReader(regionShape),NULL);

}

-(void) procesarBasesDeDatosVectoriales
{
    if(countryDb)
        countryDb->process();
}

-(WhirlyGlobe::VectorDatabase *) obtenerBDPaises
{
    return countryDb;
}

-(WhirlyGlobe::VectorDatabase *) obtenerBDOceanos
{
    return oceanDb;
};

-(WhirlyGlobe::VectorDatabase *) obtenerBDRegiones
{
    return regionDb;
}

@end
