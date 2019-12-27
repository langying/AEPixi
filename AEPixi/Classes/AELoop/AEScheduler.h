//
//  AEScheduler.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/2.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AEScheduler__
#define __AEPixi__AEScheduler__

#include "AECommon.h"

typedef std::function<GLvoid(GLfloat)> AESchedulerFunction;

class AEScheduler {
public:
    _ae_property(GLfloat, TimeScale, timeScale);
    
public:
    ~AEScheduler();
    AEScheduler();
    GLvoid update(GLfloat detalTime);
    GLvoid schedule(AESchedulerFunction& callback, GLvoid* target, GLfloat interval, GLbool paused, std::string& key);
    GLvoid schedule(AESchedulerFunction& callback, GLvoid* target, GLfloat interval, GLuint repeat, GLfloat delay, GLbool paused, std::string& key);
};

#endif /* defined(__AEPixi__AEScheduler__) */
