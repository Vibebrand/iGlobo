//
//  AppDelegate.m
//  iGlobo
//
//  Created by Jesus Cagide on 16/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "AppDelegate.h"
#import "ControladorRepresentacionGlobo.h"
#import "PantallaPrincipal.h"
#import "ControlMaestro.h"
#import "MotorSenchaAPI.h"
#import "RepresentableSencha.h"
#import "ControladorPiramidePoblacional.h"
#import "ControladorGraficaSencha.h"
#import "../libs/TestFlight/TestFlight.h"


@implementation AppDelegate

@synthesize window = _window;

- (void)dealloc
{
   
    //[_controladorRepresentacionGlobo release];
    [_pantallaPrincipal release];
    [_controlMaestro release];
    [_window release];
    [super dealloc];
}

- (void)postLaunch:(NSObject *)what
{
    // Add the view controller's view to the window and display.
    //[[_pantallaPrincipal representacionGlobo] addSubview:_controladorRepresentacionGlobo.view];
    [self.window setRootViewController: _pantallaPrincipal];
    [self.window makeKeyAndVisible];
    [_controlMaestro actualizaSecciones];
}
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
#define TESTING 1
#ifdef TESTING
    [TestFlight setDeviceIdentifier:[[UIDevice currentDevice] uniqueIdentifier]];
#endif
    
    [TestFlight takeOff:@"fc94afbf9058e48097c399875eb34c13_MTA5NjA4MjAxMi0wNy0xMiAxNDozNDowOC40ODc0MjA"];
    
    sleep(2);
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    self.window.backgroundColor = [UIColor whiteColor];
        
    ControladorGraficaSencha* controladorGraficaSenchaPie = [[[ControladorGraficaSencha alloc] initWithNibName:@"ControladorGraficaSencha" bundle:[NSBundle mainBundle]] autorelease];  
    
    

     ControladorGraficaSencha* controladorGraficaSenchaArea = [[[ControladorGraficaSencha alloc] initWithNibName:@"ControladorGraficaSencha" bundle:[NSBundle mainBundle]] autorelease] ; 
    
    
    MotorGraficasSencha::IRepresentableSencha * representable = new RepresentableSencha([controladorGraficaSenchaPie controladorSencha]);
    
    
    MotorGraficasSencha::IRepresentableSencha * representable2 = new RepresentableSencha([controladorGraficaSenchaArea controladorSencha]);
    
    MotorGraficasSencha::MotorGraficasSencha * motorGraficasSencha = new MotorGraficasSencha::MotorGraficasSencha;
    
    motorGraficasSencha->registraRepresentable(representable, "Distribucion de la poblacion no economicamente activa segun tipo de actividad", MotorGraficasSencha::MotorGraficasSencha::Pie);
    motorGraficasSencha->registraRepresentable(representable2, "Porcentaje de la poblacion segun caracteristica economica", MotorGraficasSencha::MotorGraficasSencha::Area);
    
    ControladorRepresentacionGlobo * controladorRepresentacionGlobo = [[ControladorRepresentacionGlobo alloc]  initWithNibName:@"ControladorRepresentacionGlobo" bundle:nil ];
    
    ControladorPiramidePoblacional * controladorPiramidePoblacional = [[ControladorPiramidePoblacional alloc] init];
    
    _pantallaPrincipal = [[ PantallaPrincipal alloc ] initWithNibName:@"PantallaPrincipal" bundle:[NSBundle mainBundle]];
    [_pantallaPrincipal setControladorVista: controladorRepresentacionGlobo];
    [_pantallaPrincipal setControladorPiramidePoblacional:controladorPiramidePoblacional];
    [_pantallaPrincipal setControladorGraficaPie:controladorGraficaSenchaPie];
    [_pantallaPrincipal setControladorGraficaArea:controladorGraficaSenchaArea];
    
    _controlMaestro = [ControlMaestro new];
    
    id gestorInteres = controladorRepresentacionGlobo;
    if([gestorInteres conformsToProtocol: @protocol(iGestorObjectiveC)]) {
        [_controlMaestro registraGestor: gestorInteres];
    }
    
    [_controlMaestro registraGestorCpp: motorGraficasSencha];

    gestorInteres = controladorPiramidePoblacional;
    if([gestorInteres conformsToProtocol: @protocol(iGestorObjectiveC)]) {
        [_controlMaestro registraGestor: gestorInteres];
    }

    
    [_controlMaestro cargaArchivos];
    [controladorRepresentacionGlobo release];
    [controladorPiramidePoblacional release];
    
    [self performSelectorOnMainThread:@selector(postLaunch:) withObject:nil waitUntilDone:NO];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
}

@end
