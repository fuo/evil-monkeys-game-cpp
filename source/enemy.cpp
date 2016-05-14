//
//  enemy.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "enemy.hpp"

#include "character.hpp"
#include "level.hpp"

using namespace EvilMonkeys;

#include <stdlib.h>
#include <math.h>
#include <list>

Enemy::Enemy(Level *l, DrawEngine *de, int sprite_index, float xpos, float ypos, int i_lives) : Sprite(l, de, sprite_index, xpos, ypos, i_lives)
{
    setClassID(ENEMY_CLASSID);
}

bool Enemy::move(float xDir, float yDir)
{
    int xpos = (int)(getX() + xDir);
    int ypos = (int)(getY() + yDir);
    
    if (isValidLevelMove(xpos, ypos)) {
        
        // make sure we don't run into any other enemies;
        typename std::list<Sprite *>::const_iterator Iter = level->npc.begin();
        typename std::list<Sprite *>::const_iterator itEnd = level->npc.end();
        
        for ( ; Iter != itEnd; Iter++) {
            if ((*Iter) != this && (int)(*Iter)->getX() == xpos && (int)(*Iter)->getY() == ypos) {
                
                return false;
            }
        }
        
        
        erase(getX(), getY());
        
        setPosition(getX() + xDir, getY() + yDir);
        
        facingDirection.x = xDir;
        facingDirection.y = yDir;
        
        draw(getX(), getY());
        
        if ((int)goal->getX() == xpos && (int)goal->getY() == ypos) {
            goal->__addLives(-1);
        }
        
        return true;
    }
    
    return false;
}

void Enemy::idleUpdate()
{
    if (goal->getLives() > 0)
        simulateAI();
}

void Enemy::simulateAI(void)
{
    vector goal_pos = goal->getPosition();
    vector direction;
    
    direction.x = goal_pos.x - getX();
    direction.y = goal_pos.y - getY();
    
    float mag = sqrt(direction.x * direction.x + direction.y * direction.y);
    
    direction.x = direction.x / (mag * 6);
    direction.y = direction.y / (mag * 6);
    
    char** lvl = level->createLevel();
    
    if (lvl[0][lround(direction.y)] != TILE_WALL || lvl[lround(direction.x)][0] != TILE_WALL)
    {
        if (!move(direction.x, direction.y))
        {
            if (!move(0, float(rand() % 3 - 1)))
            {
                if (!move(float(rand() % 3 - 1), 0)){ }
            }
        }
    }
    else
    {
        if (!move(0, direction.y))
        {
            if (!move(0, float(rand() % 3 - 1)))
            {
                if (!move(float(rand() % 3 - 1), 0)) { }
            }
        }
        if (!move(direction.x, 0))
        {
            if (!move(0, float(rand() % 3 - 1)))
            {
                if (!move(float(rand() % 3 - 1), 0)) { }
            }
        }
    }
    
}