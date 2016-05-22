//
//  bomb.cpp
//  evil-monkeys
//
//  Created by phuong on 5/15/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "bomb.h"

#include "level.h"

using namespace EvilMonkeys;

Bomb::Bomb(DrawEngine *de, int sprite_index, float xpos, float ypos, int i_lives) : Sprite(de, sprite_index, xpos, ypos, i_lives)
{
    
    setClassID(BOMB_CLASSID);
}

void Bomb::__idleUpdate()
{
    typename std::list<Sprite *>::const_iterator Iter = level->firstNPC();
    typename std::list<Sprite *>::const_iterator itEnd = level->lastNPC();
    
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
            
            // and kill itself
            __addLives(-1);

        }
    }
}