//
//  fireball.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "fireball.h"

#include "level.h"

using namespace EvilMonkeys;

#include <list>

Fireball::Fireball(DrawEngine *de, int sprite_index, float xpos, float ypos,
                   float xDir, float yDir, int i_lives) : Bomb(de, sprite_index, xpos, ypos, i_lives)
{
    facingDirection.x = xDir;
    facingDirection.y = yDir;
    
    setClassID(FIREBALL_CLASSID);
}

void Fireball::__idleUpdate()
{
    if (Sprite::__move(facingDirection.x, facingDirection.y))
        // kill the enemy OR Fireball got hit and then kill itself
        Bomb::__idleUpdate();
    else
        // hit the wall border
        __addLives(-1);    
}

void Fireball::__addLives(int num)
{
    Sprite::__addLives(num);
    level->updateNumFireballs(-1);
}
