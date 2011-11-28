//
//  PantallaPrincipal.m
//  iGlobo
//
//  Created by Jesus Cagide on 24/11/11.
//  Copyright (c) 2011 INEGI. All rights reserved.
//

#import "PantallaPrincipal.h"

@implementation PantallaPrincipal

@synthesize representacionGlobo = _representacionGlobo;


-(void)dealloc
{
    [_representacionGlobo release];
    [_controladorRepresentacionGlobo release];
    [super dealloc];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    _controladorRepresentacionGlobo = [[ControladorRepresentacionGlobo alloc]  initWithNibName:@"ControladorRepresentacionGlobo" bundle:nil ];
    self.representacionGlobo.layer.cornerRadius = 5;
    
    
[[self representacionGlobo] addSubview: _controladorRepresentacionGlobo.obtenerRepresentacion ];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	return YES;
}

@end
