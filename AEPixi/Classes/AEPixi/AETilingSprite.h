//
//  AETilingSprite.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/4.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AETilingSprite__
#define __AEPixi__AETilingSprite__

#include "AESprite.h"

class AETilingSprite: public AESprite {
public:
    _ae_property(AESize,  TileSize,     tileSize);
    _ae_property(AEPoint, TileScale,    tileScale);
    _ae_property(AEPoint, TilePosition, tilePosition);
    
public:
    AETilingSprite(AETexture* texture, GLfloat width, GLfloat height);
    GLvoid applyRender(AERenderer* renderer);
    AERect getBounds();
    GLfloat getTileScaleX();    GLvoid setTileScaleX(GLfloat tileScaleX);
    GLfloat getTileScaleY();    GLvoid setTileScaleY(GLfloat tileScaleY);
    GLfloat getTilePositionX(); GLvoid setTilePositionX(GLfloat tilePositionX);
    GLfloat getTilePositionY(); GLvoid setTilePositionY(GLfloat tilePositionY);
protected:

};

#endif /* defined(__AEPixi__AETilingSprite__) */
