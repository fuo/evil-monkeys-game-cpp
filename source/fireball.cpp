//
//  fireball.cpp
//  3dbuzz
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "fireball.hpp"

#include <list>
using namespace std;

#include "level.hpp"

Fireball::Fireball(Level *lvl, DrawEngine *de, int sprite_index, float xpos, float ypos,
                   float xDir, float yDir, int i_lives) : Sprite(lvl, de, sprite_index, xpos, ypos, i_lives)
{
    facingDirection.x = xDir;
    facingDirection.y = yDir;
    
    setClassID(FIREBALL_CLASSID);
}

void Fireball::idleUpdate()
{
    if (Sprite::move(facingDirection.x, facingDirection.y))
    {
        for (list <Sprite *>::iterator Iter = level->npc.begin(); Iter != level->npc.end(); Iter++)
        {
            if (
                 (*Iter)->getClassID() != this->getClassID() &&
                 (int)(*Iter)->getX() == this->getX() &&
                 (int)(*Iter)->getY() == this->getY()
               )
            {                
                // kill the enemy got hit
                (*Iter)->addLives(-1);
                --(level->numEnemies);
                
                // kill that fireball itself
                addLives(-1);
            }
        }
    }
    else
    {
        // hit the wall border
        addLives(-1);
    }
}