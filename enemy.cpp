//
//  enemy.cpp
//  3dbuzz
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include <list>

#include "enemy.hpp"
#include "character.hpp"

Enemy::Enemy(Level *l, DrawEngine *de, int s_index, float x, float y, int i_lives) : Sprite(l, de, s_index, x ,y , i_lives)
{
    goal = 0;
    
    classID = ENEMY_CLASSID;
}

bool Enemy::move(float x, float y)
{
    int xpos = (int)(pos.x + x);
    int ypos = (int)(pos.y + y);
    
    if (isValidLevelMove(xpos, ypos)) {
        
        // make sure we don't run into any other enemies;
        list <Sprite *>::iterator Iter;
        
        for (Iter = level->npc.begin(); Iter != level->npc.end(); Iter++) {
            if ((*Iter) != this && (int)(*Iter)->getX() == xpos && (int)(*Iter)->getY() == ypos) {
                
                return false;
            }
        }
        
        
        erase(pos.x, pos.y);
        
        pos.x += x;
        pos.y += y;
        
        facingDirection.x = x;
        facingDirection.y = y;
        
        draw(pos.x, pos.y);
        
        if ((int)goal->getX() == xpos && (int)goal->getY() == ypos) {
            goal->addLives(-1);
        }
        
        return true;
    }
    
    return false;
}

void Enemy::idleUpdate()
{
    if (goal)
        simulateAI();
    
}

void Enemy::addGoal(Character *g)
{
    
    goal = g;
}

void Enemy::simulateAI(void)
{
    vector goal_pos = goal->getPosition();
    vector direction;
    
    direction.x = goal_pos.x - pos.x;
    direction.y = goal_pos.y - pos.y;
    
    float mag = sqrt(direction.x * direction.x + direction.y * direction.y);
    
    // get the unit vector 1 in length
    direction.x = direction.x / (mag * 9);
    direction.y = direction.y / (mag * 9);
    
//    if (!move(direction.x, direction.y)) {
//        while (!move(float(rand() % 3 - 1), float(rand() % 3 - 1))) {
//            
//        }
//    }
    
    if (level->level[0][(int)direction.y] != TILE_WALL || level->level[(int)direction.x][0] != TILE_WALL){
        if (!move(direction.x, direction.y)) {
            //            while (!move(float(rand() % 3 - 1), float(rand() % 3 - 1))) {
            //
            //            }
            if (!move(0, float(rand() % 3 - 1))) {
                if (!move(float(rand() % 3 - 1), 0)) {
                    
                }
            }
            
        }
    } else {
        if (!move(0, direction.y)) {
            if (!move(0, float(rand() % 3 - 1))) {
                if (!move(float(rand() % 3 - 1), 0)) {
                    
                }
            }
        }
        if (!move(direction.x, 0)) {
            if (!move(0, float(rand() % 3 - 1))) {
                if (!move(float(rand() % 3 - 1), 0)) {
                    
                }
            }
        }
    }

}