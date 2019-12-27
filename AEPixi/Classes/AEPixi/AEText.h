//
//  AEText.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/14.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AEText__
#define __AEPixi__AEText__

#include "AEFont.h"
#include "AESprite.h"

class AEText: public AESprite {
public:
    _ae_property(String,  Text, text);
    _ae_property(AEFont*, Font, font);

public:
    ~AEText();
    AEText(String& text);
    
protected:
    GLvoid updateTexture();
    String pathfont(String name);
};

#endif /* defined(__AEPixi__AEText__) */
