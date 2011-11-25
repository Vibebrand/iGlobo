//
//  PantallaPrincipal.h
//  iGlobo
//
//  Created by Jesus Cagide on 24/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ControladorRepresentacionGlobo.h"

@interface PantallaPrincipal : UIViewController
{
    UIView * _representacionGlobo;
    ControladorRepresentacionGlobo *_controlador;
}

@property(nonatomic, retain)IBOutlet UIView* representacionGlobo;

@end
