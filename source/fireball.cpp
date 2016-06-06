//
//  fireball.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "fireball.h"

void Target::Fireball::__idleUpdate()
{
    if (Sprite::__move(facingDirection_.x, facingDirection_.y))
        // kill the enemy OR Fireball got hit and then kill itself
        Bomb::__idleUpdate();
    else
        // hit the wall border
        __addLives(-1);    
}