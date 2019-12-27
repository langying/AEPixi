//
//  AEViewController.m
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/7/24.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#import <GLKit/GLKit.h>
#import "AEViewController.h"

#include "AJPixi.h"

const char* TouchStart = "touchStart";
const char* TouchMove  = "touchMove";
const char* TouchEnd   = "touchEnd";

@interface AEViewController()<GLKViewDelegate>

@property(nonatomic, assign) AJPixi*   pixi;
@property(nonatomic, strong) UILabel*  label;
@property(nonatomic, strong) GLKView*  glview;
@property(nonatomic, strong) NSString* gamefile;
@property(nonatomic, strong) NSString* pixifile;
@property(nonatomic, strong) CADisplayLink* timer;

@end

@implementation AEViewController
- (void)dealloc {
    _ae_delete(self.pixi);
}

- (instancetype)initWithGame:(NSString*)gamefile {
    if ((self = [super init]) == nil) {
        return nil;
    }
    self.gamefile = @"http://download.taobaocdn.com/appengine-download/test/pixi003/index.js";
    self.pixifile = [NSBundle.mainBundle pathForResource:@"web/sdks/aepixi.js" ofType:nil];
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    [self.view addSubview:({
        EAGLContext* context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        [EAGLContext setCurrentContext:context];
        
        GLKView* glview = [[GLKView alloc] initWithFrame:self.view.bounds context:context];
        glview.opaque                 = YES;
        glview.delegate               = self;
        glview.enableSetNeedsDisplay  = NO;
        glview.userInteractionEnabled = NO;
        glview.drawableMultisample    = GLKViewDrawableMultisampleNone;
        glview.drawableDepthFormat    = GLKViewDrawableDepthFormat24;
        glview.drawableStencilFormat  = GLKViewDrawableStencilFormat8;
        glview.drawableColorFormat    = GLKViewDrawableColorFormatRGBA8888;
        [self.glview bindDrawable];
        self.glview = glview;
    })];
    [self.view addSubview:({
        UILabel* label = [UILabel.alloc initWithFrame:CGRectMake(0, 64, 44, 20)];
        label.backgroundColor = [UIColor clearColor];
        label.font = [UIFont systemFontOfSize:14];
        label.textColor = [UIColor whiteColor];
        self.label = label;
    })];
    self.pixi = new AJPixi(self.pixifile.UTF8String);
    self.pixi->loadGame(self.gamefile.UTF8String);
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.timer = ({
        CADisplayLink* display = [CADisplayLink displayLinkWithTarget:self selector:@selector(fps)];
        [display addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        display.frameInterval = 1;
        display;
    });
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [self.timer invalidate];
    self.timer = nil;
}

- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event {
    [super touchesBegan:touches withEvent:event];
    [self touches:touches function:TouchStart];
}
- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event {
    [super touchesMoved:touches withEvent:event];
    [self touches:touches function:TouchMove];
}
- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event {
    [super touchesEnded:touches withEvent:event];
    [self touches:touches function:TouchEnd];
}
- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event {
    [super touchesCancelled:touches withEvent:event];
    [self touches:touches function:TouchEnd];
}
- (void)touches:(NSSet*)touches function:(const char*)function {
    AEPointList points;
    for (UITouch* touch in touches) {
        CGPoint pt = [touch locationInView:self.glview];
        points.push_back(AEPointMake(pt.x * 2, pt.y * 2));
    }
    self.pixi->onTouch(points, function);
}

#pragma mark - 渲染循环
- (void)fps {
    static GLuint FPS = 0;
    static NSTimeInterval LastFpsTime = 0;
    
    FPS++;
    NSTimeInterval time = self.timer.timestamp;
    if (time - LastFpsTime >= 1.0f) {
        NSString* title = [NSString stringWithFormat:@"%d fps", FPS];
        NSLog(@"%@", title);
        self.label.text = title;
        FPS = 0;
        LastFpsTime = time;
    }
    [self.glview display];
}

#pragma mark - GLKViewDelegate
- (void)glkView:(GLKView*)view drawInRect:(CGRect)rect {
    self.pixi->onLoop();
    CheckGlError();
}

@end
