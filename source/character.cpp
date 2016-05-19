//
//  character.cpp
//  evil-monkeys
//
//  Created by phuong on 5/11/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "character.h"
using namespace EvilMonkeys;

Character::Character(DrawEngine* de, int s_index, float xpos, float ypos, int lives,
                     int up_key, int down_key, int left_key, int right_key) : Sprite(de, s_index, xpos, ypos, lives)
{
    i_upKey = up_key;
    i_downKey = down_key;
    i_leftKey = left_key;
    i_rightKey = right_key;
    
    setClassID(CHARACTER_CLASSID);
    
}

bool Character::__isKeyPressExecuteAction(int key)
{
    switch(key)
    {	case KEY_UP:
            return __move(0, -1);

        case KEY_DOWN:
            return __move(0, 1);

        case KEY_RIGHT:
            return __move(1, 0);

        case KEY_LEFT:
            return __move(-1, 0);

        default:
            break;
    }
    
    return false;
}

void Character::__addLives(int num)
{
    Sprite::__addLives(num);
    
    if (getLives() > 0) {
        // reset or re-spawn the position
        setPosition(1, 1);
        draw_();
    }
}

bool Character::__move(float xDir, float yDir)
{
    return Sprite::__move(xDir, yDir);
}