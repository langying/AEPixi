//
//  AETouch.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/11.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AETouch__
#define __AEPixi__AETouch__

#include "AENode.h"

class AETouch {
public:
    _ae_property(AEPoint, Global, global);
    
public:
    AEPoint getLocalPosition(AENode* node);
protected:
};

#endif /* defined(__AEPixi__AETouch__) */
