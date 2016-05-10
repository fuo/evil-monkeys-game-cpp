//
//  sprite.cpp
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "sprite.hpp"

Sprite::Sprite(DrawEngine *de, int s_index, float xpos, float ypos, int i_lives)
{
    drawArea = de;
    
    pos.x = xpos;
    pos.y = ypos;
    
    spriteIndex = s_index;
    
    numLives = i_lives;
    
    facingDirection.x = 1;
    facingDirection.y = 0;
    
    classID = SPRITE_CLASSID;
}

Sprite::~Sprite()
{
    //erase the dying sprites
    erase(pos.x, pos.y);
}

bool Sprite::move(float xDir, float yDir)
{
    erase(pos.x, pos.y);
    
    pos.x += xDir;
    pos.y += yDir;
    
    facingDirection.x = xDir;
    facingDirection.y = yDir;
    
    draw(pos.x, pos.y);
    
    return true;
}
