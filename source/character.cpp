//
//  character.cpp
//  evil-monkeys
//
//  Created by phuong on 5/11/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "character.hpp"

using namespace EvilMonkeys;

Character::Character(Level *l, DrawEngine* de, int s_index, float xpos, float ypos, int lives,
                     int up_key, int down_key, int left_key, int right_key) : Sprite(l, de, s_index, xpos, ypos, lives)
{
    i_upKey_ = up_key;
    i_downKey_ = down_key;
    i_leftKey_ = left_key;
    i_rightKey_ = right_key;
    
    setClassID(CHARACTER_CLASSID);
    
}

bool Character::__isKeyPressExecuteAction(int key)
{
    switch(key)
    {	case KEY_UP:
            drawArea->createSprite(SPRITE_PLAYER, '^');
            return move(0, -1);
            break;
        case KEY_DOWN:
            drawArea->createSprite(SPRITE_PLAYER, 'v');
            return move(0, 1);
            break;
        case KEY_RIGHT:
            drawArea->createSprite(SPRITE_PLAYER, '>');
            return move(1, 0);
            break;
        case KEY_LEFT:            
            drawArea->createSprite(SPRITE_PLAYER, '<');
            return move(-1, 0);
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
        draw(getX(), getY());
    }
}