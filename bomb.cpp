//
//  bomb.cpp
//  evil-monkeys
//
//  Created by phuong on 5/15/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "bomb.hpp"

using namespace EvilMonkeys;

Bomb::Bomb(Level *lvl, DrawEngine *de, int sprite_index, float xpos, float ypos, int i_lives) : Sprite(lvl, de, sprite_index, xpos, ypos, i_lives)
{
    
    setClassID(BOMB_CLASSID);
}

void Bomb::__idleUpdate()
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
            // kill the enemy OR Fireball got hit
            (*Iter)->__addLives(-1);
            
            if ((*Iter)->getClassID() == ENEMY_CLASSID)
                --(level->numEnemies);
            
            // and kill itself
            __addLives(-1);

        }
    }
}