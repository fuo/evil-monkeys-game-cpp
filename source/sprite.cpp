//
//  sprite.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "sprite.h"

#include "level.h"
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
}

bool Sprite::__move(float xDir, float yDir)
{
    vector target;
    
    target.x = pos.x + xDir;
    target.y = pos.y + yDir;

    if ( isValidLevelMove(target.x, target.y) )
    {
        // update the facing direction before move
        facingDirection.x = xDir;
        facingDirection.y = yDir;

        // erase sprite at current position

        if ( level->checkMapTileEmpty(pos.x, pos.y, SPRITE_PLAYER) )
            erase_();

        // update its pos to the target position
        setPosition(target.x, target.y);

        // draw itseft with its new position
        draw_();

        return true;
    }

    return false;
}

void Sprite::draw_(float x, float y){

    if (x < 0)
        x = pos.x;

    if (y < 0)
        y = pos.y;

    drawArea->drawSprite_(spriteIndex, (int)x, (int)y);
}

bool Sprite::isValidLevelMove(int xpos, int ypos)
{
    if (!level)
        return false;

    // check inside level
    if ( level->checkMapTileEmpty(xpos, ypos) )
        return true;

    return false;
}

bool Sprite::matchCurrentLocation(int xpos, int ypos)
{
    return ( (int)pos.x == xpos && (int)pos.y == ypos );
}

void Sprite::__hookToLevel(Level* lvl, bool draw_at_once)
{
    if (draw_at_once)
        // display itseft to the world right after born
        draw_();

    level = lvl;
}