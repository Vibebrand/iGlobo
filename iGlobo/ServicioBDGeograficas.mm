//
//  ServicioBDGeograficas.m
//  iGlobo
//
//  Created by Jesus Cagide on 18/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "ServicioBDGeograficas.h"

@implementation ServicioBDGeograficas


-(id)init
{
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


@end
