//
//  AppDelegate.h
//  iGlobo
//
//  Created by Jesus Cagide on 16/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import <UIKit/UIKit.h>
//@class ControladorRepresentacionGlobo;
@class PantallaPrincipal;
@class ControlMaestro;

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
   // ControladorRepresentacionGlobo *_controladorRepresentacionGlobo;
    PantallaPrincipal *_pantallaPrincipal;
    ControlMaestro * _controlMaestro;
}

@property (strong, nonatomic) UIWindow *window;

@end
