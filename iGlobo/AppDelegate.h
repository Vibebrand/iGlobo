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


@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
   // ControladorRepresentacionGlobo *_controladorRepresentacionGlobo;
    PantallaPrincipal *_pantallaPrincipal;
}

@property (strong, nonatomic) UIWindow *window;

@end
