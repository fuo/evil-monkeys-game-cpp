//
//  sprite.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "sprite.hpp"

#include "level.hpp"

using namespace EvilMonkeys;

Sprite::Sprite(Level* lvl, DrawEngine *de, int sprite_index, float xpos, float ypos, int i_lives)
{
    drawArea = de;
    
    pos.x = xpos;
    pos.y = ypos;
    
    spriteIndex = sprite_index;
    
    numLives = i_lives;
    
    facingDirection.x = 1;
    facingDirection.y = 0;
    
    classID = SPRITE_CLASSID;
    
    level = lvl;
    
    draw(pos.x, pos.y);
}

bool Sprite::move(float xDir, float yDir)
{
    vector direction;
    
    direction.x = (int)(pos.x + xDir);
    direction.y = (int)(pos.y + yDir);
    
    if ( isValidLevelMove(direction.x, direction.y) )
    {
        facingDirection.x = xDir;
        facingDirection.y = yDir;
        
        // erase sprite
        erase(pos.x, pos.y);
        
        setPosition(direction.x, direction.y);
        
        // draw sprite
        draw(pos.x, pos.y);
        
        return true;
    }
    
    return false;
}

bool Sprite::isValidLevelMove(int xpos, int ypos)
{
    char** lvl = level->createLevel();
    // check inside level
    if (lvl[xpos][ypos] != TILE_WALL)
        return true;
    
    return false;
}