//
//  AEScheduler.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/2.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AEScheduler.h"

//GLvoid AEScheduler::schedule(AESchedulerFunction &callback, GLvoid *target, GLfloat interval, GLuint repeat, GLfloat delay, GLbool paused, std::string& key) {    
//    tHashTimerEntry *element = nullptr;
//    HASH_FIND_PTR(_hashForTimers, &target, element);
//    
//    if (! element)
//    {
//        element = (tHashTimerEntry *)calloc(sizeof(*element), 1);
//        element->target = target;
//        
//        HASH_ADD_PTR(_hashForTimers, target, element);
//        
//        // Is this the 1st element ? Then set the pause level to all the selectors of this target
//        element->paused = paused;
//    }
//    else
//    {
//        CCASSERT(element->paused == paused, "");
//    }
//    
//    if (element->timers == nullptr)
//    {
//        element->timers = ccArrayNew(10);
//    }
//    else
//    {
//        for (int i = 0; i < element->timers->num; ++i)
//        {
//            TimerTargetCallback *timer = dynamic_cast<TimerTargetCallback*>(element->timers->arr[i]);
//            
//            if (timer && key == timer->getKey())
//            {
//                CCLOG("CCScheduler#scheduleSelector. Selector already scheduled. Updating interval from: %.4f to %.4f", timer->getInterval(), interval);
//                timer->setInterval(interval);
//                return;
//            }
//        }
//        ccArrayEnsureExtraCapacity(element->timers, 1);
//    }
//    
//    TimerTargetCallback *timer = new (std::nothrow) TimerTargetCallback();
//    timer->initWithCallback(this, callback, target, key, interval, repeat, delay);
//    ccArrayAppendObject(element->timers, timer);
//    timer->release();
//
//}

