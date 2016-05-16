//
//  fireball.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "fireball.hpp"

#include "level.hpp"

using namespace EvilMonkeys;

#include <list>

Fireball::Fireball(Level *lvl, DrawEngine *de, int sprite_index, float xpos, float ypos,
                   float xDir, float yDir, int i_lives) : Bomb(lvl, de, sprite_index, xpos, ypos, i_lives)
{
    facingDirection.x = xDir;
    facingDirection.y = yDir;
    
    setClassID(FIREBALL_CLASSID);
}

void Fireball::__idleUpdate()
{
    if (Sprite::__move(facingDirection.x, facingDirection.y))
    {
        typename std::list<Sprite *>::const_iterator Iter = level->npc.begin();
        typename std::list<Sprite *>::const_iterator itEnd = level->npc.end();
        
        for( ; Iter != itEnd; ++Iter )
        {
            if (
                 (*Iter)->getClassID() != this->getClassID() &&
                 (int)(*Iter)->getX() == this->getX() &&
                 (int)(*Iter)->getY() == this->getY()
               )
            {                
                // kill the enemy OR Bomb got hit
                (*Iter)->__addLives(-1);
                
                if ((*Iter)->getClassID() == ENEMY_CLASSID)
                    --(level->numEnemies);
                
                // kill that fireball itself
                __addLives(-1);
                --(level->numFireballs);
            }
        }
    }
    else
    {
        // hit the wall border
        __addLives(-1);
        --(level->numFireballs);
    }
}