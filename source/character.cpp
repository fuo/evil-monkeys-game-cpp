//
//  character.cpp
//  evil-monkeys
//
//  Created by phuong on 5/11/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "level.h"

using namespace EvilMonkeys;

bool Character::__isKeyPressExecuteAction(int key)
{
    switch(key)
    {	case KEY_UP:
            drawArea_->registerSprite(SPRITE_PLAYER, '^');
            return __move(0, -1);

        case KEY_DOWN:
            drawArea_->registerSprite(SPRITE_PLAYER, 'v');
            return __move(0, 1);

        case KEY_RIGHT:
            drawArea_->registerSprite(SPRITE_PLAYER, '>');
            return __move(1, 0);

        case KEY_LEFT:
            drawArea_->registerSprite(SPRITE_PLAYER, '<');
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
        resetPosition();
        
        level_->pause();
    }
}

bool Character::__hookToLevel(Level* lvl, bool draw_at_once)
{
    if (Sprite::__hookToLevel(lvl, draw_at_once))
        return level_->addPlayer(this);

    return false;
}

bool Character::checkSafeSpawnPosition(int xpos, int ypos, int distance_to_player)
{
    return (distance_to_player < 0) ? true : (xpos > pos_.x + distance_to_player || ypos > pos_.y + distance_to_player);
}