//
//  character.cpp
//  evil-monkeys
//
//  Created by phuong on 5/11/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "character.hpp"

Character::Character(Level *l, DrawEngine* de, int s_index, float xpos, float ypos, int lives,
                     int up_key, int down_key, int left_key, int right_key) : Sprite(l, de, s_index, xpos, ypos, lives)
{
    upKey = up_key;
    downKey = down_key;
    leftKey = left_key;
    rightKey = right_key;
    
    classID = CHARACTER_CLASSID;
    
}

Character::~Character()
{
    
}

bool Character::keyPress(int key)
{
    switch(key)
    {	case KEY_UP:
            return move(0, -1);
            break;
        case KEY_DOWN:
            return move(0, 1);
            break;
        case KEY_RIGHT:
            return move(1, 0);
            break;
        case KEY_LEFT:
            return move(-1, 0);
        default:
            break;
    }
    
    return false;
}