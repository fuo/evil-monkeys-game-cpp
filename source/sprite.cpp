//
//  sprite.cpp
//  3dbuzz
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include <iostream>

#include "sprite.hpp"


using namespace::std;

Sprite::Sprite(Level *l, DrawEngine *de, int s_index, float x, float y, int i_lives){
    drawArea = de;
    
    pos.x = x;
    pos.y = y;
    
    spriteIndex = s_index;
    
    numLives = i_lives;
    
    facingDirection.x = 1;
    facingDirection.y = 0;
    
    classID = SPRITE_CLASSID;
    
    level = l;
}

Sprite::~Sprite()
{
    // erase the dying sprites
    erase(pos.x, pos.y);
}

vector Sprite::getPosition()
{
    return pos;
}

float Sprite::getX(){
    return pos.x;
}

float Sprite::getY()
{
    return pos.y;
}

void Sprite::addLives(int num){
    numLives += num;
}

int Sprite::getLives()
{
    return numLives;
}

bool Sprite::isAlive()
{
    return (numLives > 0);
}

bool Sprite::move(float x, float y)
{
    
    int xpos = (int)(pos.x + x);
    int ypos = (int)(pos.y + y);
    
    if (isValidLevelMove(xpos, ypos)) {
        
        
        
        // erase sprite
        erase(pos.x, pos.y);
        
        pos.x += x;
        pos.y += y;
        
        facingDirection.x = x;
        facingDirection.y = y;
        
        // draw sprite
        draw(pos.x, pos.y);
        
        //    x = ((int)x + 1) % drawArea->getWindowWidth();
        return true;
    }
    
    return false;
}

void Sprite::draw(float x, float y)
{
    drawArea->drawSprite(spriteIndex, (int)x, (int)y);
}

void Sprite::erase(float x, float y)
{
    drawArea->eraseSprite((int)x, (int)y);
}

bool Sprite::isValidLevelMove(int xpos, int ypos)
{
    // check inside level
    if (level->level[xpos][ypos] != TILE_WALL)
        return true;
    
    
    return false;
    
}

void Sprite::idleUpdate(){
    // this is only for the inhereited classes not for myself
}