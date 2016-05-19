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

    // face to the right at spawn time
    facingDirection.x = 1;
    facingDirection.y = 0;
    
    classID = SPRITE_CLASSID;

    // draw itself on the screen so the world can see me
    draw();
}

bool Sprite::__move(float xDir, float yDir)
{
    facingDirection.x = xDir;
    facingDirection.y = yDir;

    vector target;
    
    target.x = pos.x + xDir;
    target.y = pos.y + yDir;

    // erase sprite at current before move
    erase();

    // update its pos to the target position
    setPosition(target.x, target.y);
    
    // draw itseft with its new position
    draw();
    
    return true;

}

void Sprite::draw_(float x, float y){

    if (x < 0)
        x = pos.x;

    if (y < 0)
        y = pos.y;

    drawArea->drawSprite_(spriteIndex, (int)x, (int)y);
}
