//
//  character.cpp
//  evil-monkeys
//
//  Created by phuong on 5/11/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "character.h"

#include "level.h"
using namespace EvilMonkeys;

Character::Character(DrawEngine* de, int s_index, float xpos, float ypos, int lives,
                     int up_key, int down_key, int left_key, int right_key) : Sprite(de, s_index, xpos, ypos, lives)
{
    i_upKey = up_key;
    i_downKey = down_key;
    i_leftKey = left_key;
    i_rightKey = right_key;
    
    setClassID(CHARACTER_CLASSID);
    
    nonNPC();
}

bool Character::__isKeyPressExecuteAction(int key)
{
    switch(key)
    {	case KEY_UP:
            drawArea->registerSprite(SPRITE_PLAYER, '^');
            return __move(0, -1);

        case KEY_DOWN:
            drawArea->registerSprite(SPRITE_PLAYER, 'v');
            return __move(0, 1);

        case KEY_RIGHT:
            drawArea->registerSprite(SPRITE_PLAYER, '>');
            return __move(1, 0);

        case KEY_LEFT:
            drawArea->registerSprite(SPRITE_PLAYER, '<');
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
        
        level->pause();
    }
}

bool Character::__move(float xDir, float yDir)
{
    int xpos = (int)(getX() + xDir);
    int ypos = (int)(getY() + yDir);

    if (isValidLevelMove(xpos, ypos)) {

        facingDirection.x = xDir;
        facingDirection.y = yDir;

        // collect the bomb when passing by it
        typename std::list<Sprite *>::const_iterator Iter = level->firstNPC();
        typename std::list<Sprite *>::const_iterator itEnd = level->lastNPC();

        for ( ; Iter != itEnd; ++Iter) {
            if ((*Iter)->matchCurrentLocation(xpos, ypos) && (*Iter)->getClassID() == BOMB_CLASSID) {

                level->removeNPC(*Iter--);

                level->updateNumBombs(-1);
            }
        }


        erase_();

        setPosition(getX() + xDir, getY() + yDir);

        draw_();

        return true;
    }

    return false;
}

bool Character::__hookToLevel(Level* lvl, bool draw_at_once)
{
    if (Sprite::__hookToLevel(lvl, draw_at_once))
    {
        level->addPlayer(this);
        return true;
    }

    return false;
}

bool Character::checkSafeSpawnPosition(int xpos, int ypos, int distance_to_player)
{
    return (distance_to_player < 0) ? true : (xpos > pos.x + distance_to_player || ypos > pos.y + distance_to_player);
}