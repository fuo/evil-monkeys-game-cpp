//
//  enemy.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "enemy.h"

#include "level.h"
using namespace EvilMonkeys;

#include <stdlib.h>
#include <math.h>

Enemy::Enemy(DrawEngine *de, int sprite_index, float xpos, float ypos, int i_lives) : Sprite(de, sprite_index, xpos, ypos, i_lives)
{
    setClassID(ENEMY_CLASSID);
}

bool Enemy::__move(float xDir, float yDir)
{
    int xpos = (int)(getX() + xDir);
    int ypos = (int)(getY() + yDir);
    
    if (isValidLevelMove(xpos, ypos)) {

        facingDirection.x = xDir;
        facingDirection.y = yDir;

        // make sure we don't run into any other enemies;
        typename std::list<Sprite *>::const_iterator Iter = level->firstNPC();
        typename std::list<Sprite *>::const_iterator itEnd = level->lastNPC();

        for ( ; Iter != itEnd; Iter++) {
            if ((*Iter) != this && (*Iter)->matchCurrentLocation(xpos, ypos) && (*Iter)->getClassID() != BOMB_CLASSID) {
                
                return false;
            }
        }
        
        
        erase_();
        
        setPosition(getX() + xDir, getY() + yDir);
        
        draw_();

        // hit and kill the player
        if ((int)goal->getX() == xpos && (int)goal->getY() == ypos)
            goal->__addLives(-1);

        return true;
    }
    
    return false;
}

void Enemy::__idleUpdate()
{
    if (goal->getLives() > 0)
        simulateAI_();
}

void Enemy::simulateAI_(void)
{
    vector goal_pos = goal->getPosition();
    
    if (goal_pos.x == getX() && goal_pos.y == getY()) {
        __move(0, 0);
        return;
    }
    
    vector direction;
    
    direction.x = goal_pos.x - getX();
    direction.y = goal_pos.y - getY();
    
    float mag = sqrt(direction.x * direction.x + direction.y * direction.y);
    
    direction.x = direction.x / (mag * 6);
    direction.y = direction.y / (mag * 6);

    if ( level->checkMapTileEmpty( 0, (int)lround(direction.y) ) || level->checkMapTileEmpty( (int)lround(direction.x), 0 ) )
    {
        if (!__move(direction.x, direction.y))
            if (!__move(0, float(rand() % 3 - 1)))
                __move(float(rand() % 3 - 1), 0);

    }
    else
    {
        if (!__move(0, direction.y))
            if (!__move(0, float(rand() % 3 - 1)))
                __move(float(rand() % 3 - 1), 0);


        if (!__move(direction.x, 0))
            if (!__move(0, float(rand() % 3 - 1)))
                __move(float(rand() % 3 - 1), 0);

    }
    
}