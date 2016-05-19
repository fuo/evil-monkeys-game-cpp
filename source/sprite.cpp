//
//  sprite.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "sprite.h"

using namespace EvilMonkeys;

Sprite::Sprite(DrawEngine *de, int sprite_index, float xpos, float ypos, int i_lives)
{
    drawArea = de;
    
    pos.x = xpos;
    pos.y = ypos;
    
    spriteIndex = sprite_index;
    
    numLives = i_lives;
    
    facingDirection.x = 1;
    facingDirection.y = 0;
    
    classID = SPRITE_CLASSID;

    // draw itself on the screen so the world can see me
    draw(pos.x, pos.y);
}

bool Sprite::__move(float xDir, float yDir)
{
    vector direction;
    
    direction.x = (int)(pos.x + xDir);
    direction.y = (int)(pos.y + yDir);
    

    facingDirection.x = xDir;
    facingDirection.y = yDir;
    
    // erase sprite
    erase(pos.x, pos.y);
    
    setPosition(direction.x, direction.y);
    
    // draw sprite
    draw(pos.x, pos.y);
    
    return true;

}

void Sprite::draw(float x, float y, int color){
    if (color)
        drawArea->drawSprite(spriteIndex, (int)x, (int)y, color);
    else
        drawArea->drawSprite(spriteIndex, (int)x, (int)y);
}
