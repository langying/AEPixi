//
//  AETouch.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/11.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AETouch.h"

_ae_synthesize(AETouch, AEPoint, Global, global);

AEPoint AETouch::getLocalPosition(AENode* node) {
    AETransform wt = node->worldTransform();
    return AEVectorApplyInvertTransform(_global, wt);
}

