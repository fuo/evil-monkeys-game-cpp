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
            if(__move(0, -1)){
                if (!level->isRunning)
                    level->isRunning = true;
                return true;
            }
            return false;
            break;
        case KEY_DOWN:
            drawArea->createSprite(SPRITE_PLAYER, 'v');
            if(__move(0, 1)){
                if (!level->isRunning)
                    level->isRunning = true;
                return true;
            }
               return false;
            break;
        case KEY_RIGHT:
            drawArea->createSprite(SPRITE_PLAYER, '>');
            if(__move(1, 0)){
                if (!level->isRunning)
                    level->isRunning = true;
                return true;
            }
            return false;
            break;
        case KEY_LEFT:            
            drawArea->createSprite(SPRITE_PLAYER, '<');
            if(__move(-1, 0)){
                if (!level->isRunning)
                    level->isRunning = true;
                return true;
            }
            return false;
            break;
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

bool Character::__move(float xDir, float yDir)
{
    int xpos = (int)(getX() + xDir);
    int ypos = (int)(getY() + yDir);
    
    if (isValidLevelMove(xpos, ypos)) {
        
        // make sure we don't run into any other enemies;
        typename std::list<Sprite *>::const_iterator Iter = level->npc.begin();
        typename std::list<Sprite *>::const_iterator itEnd = level->npc.end();
        
        for ( ; Iter != itEnd; Iter++) {
            if ( (int)(*Iter)->getX() == xpos && (int)(*Iter)->getY() == ypos && (*Iter)->getClassID() == BOMB_CLASSID) {
                
                (*Iter)->__addLives(-1);
                Sprite* temp = *Iter;
                --Iter;
                delete temp;
                level->npc.remove(temp);
                
                --(level->numBombs);
            }
        }
        
        
        erase(getX(), getY());
        
        setPosition(getX() + xDir, getY() + yDir);
        
        facingDirection.x = xDir;
        facingDirection.y = yDir;
        
        draw(getX(), getY());
        
        
        
        return true;
    }
    
    return false;
}