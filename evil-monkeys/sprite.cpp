//
//  sprite.cpp
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "sprite.hpp"
#include "level.hpp"

Sprite::Sprite(Level *l, DrawEngine *de, int s_index, float xpos, float ypos, int i_lives)
{
    drawArea = de;
    level = l;
    
    pos.x = xpos;
    pos.y = ypos;
    
    spriteIndex = s_index;
    
    numLives = i_lives;
    
    facingDirection.x = 1;
    facingDirection.y = 0;
    
    classID = SPRITE_CLASSID;
    
    draw(pos.x, pos.y);
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

bool Sprite::isValidLevelMove(int xpos, int ypos)
{
    
    
    // check inside level
    if (level->level[xpos][ypos] != TILE_WALL)
        return true;
    
    
    return false;
    
}