//
//  AppDelegate.m
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/5/28.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions {
    self.window = [UIWindow.alloc initWithFrame:[UIScreen mainScreen].bounds];
    self.window.backgroundColor    = UIColor.blackColor;
    self.window.rootViewController = [UINavigationController.alloc initWithRootViewController:ViewController.new];
    [self.window makeKeyAndVisible];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication*)application {
}

- (void)applicationDidEnterBackground:(UIApplication*)application {
}

- (void)applicationWillEnterForeground:(UIApplication*)application {
}

- (void)applicationDidBecomeActive:(UIApplication*)application {
}

- (void)applicationWillTerminate:(UIApplication*)application {
}

@end
