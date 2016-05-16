//
//  mage.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "mage.hpp"

#include "level.hpp"
#include "fireball.hpp"
#include "bomb.hpp"

using namespace EvilMonkeys;

Mage::Mage(Level *l, DrawEngine *de, int sprite_index, float xpos, float ypos,
           int lives, char spellK, char bombK, int up_key, int down_key, int left_key, int right_key) : Character(l, de, sprite_index, xpos, ypos, lives, up_key, down_key, left_key, right_key)
{
    spellKey = spellK;
    bombKey = bombK;
    setClassID(MAGE_CLASSID);
}

bool Mage::__isKeyPressExecuteAction(int key)
{
    if (!Character::__isKeyPressExecuteAction(key))
    {
        if (key == spellKey)
        {
            if( !isValidLevelMove(getX() + facingDirection.x, getY() + facingDirection.y) || level->numFireballs > 0)
                return false;
            
            if (!level->isRunning)
                level->isRunning = true;
            
            return castSpell();
        }
        
        if (key == bombKey) {
            if( !isValidLevelMove(getX() + facingDirection.x, getY() + facingDirection.y) || level->numBombs >= level->maxBombsAllow )
                return false;
            
            if (!level->isRunning)
                level->isRunning = true;
            
            return castBomb();
        }
    }
    return false;
}

bool Mage::castBomb()
{
    Bomb* b = new Bomb(level, drawArea, SPRITE_BOMB, (int)getX()+facingDirection.x, (int)getY()+facingDirection.y);
 
    level->addNPC((Sprite*)b);
    
    ++(level->numBombs);
    
    return true;
}

bool Mage::castSpell()
{
    if ( (facingDirection.x == 0 && facingDirection.y == -1) || (facingDirection.x == 0 && facingDirection.y == 1) ) {
        drawArea->createSprite(SPRITE_FIREBALL, '|');
    }
    if ( (facingDirection.x == -1 && facingDirection.y == 0) || (facingDirection.x == 1 && facingDirection.y == 0) ) {
        drawArea->createSprite(SPRITE_FIREBALL, '-');
    }

    Fireball *temp = new Fireball(level, drawArea, SPRITE_FIREBALL, (int)getX()+facingDirection.x, (int)getY()+facingDirection.y, facingDirection.x, facingDirection.y);
    
    level->addNPC((Sprite *)temp);
    
    ++(level->numFireballs);
    
    return true;
}