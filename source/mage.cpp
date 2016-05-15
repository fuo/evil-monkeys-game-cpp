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

using namespace EvilMonkeys;

Mage::Mage(Level *l, DrawEngine *de, int sprite_index, float xpos, float ypos,
           int lives, char spellK, int up_key, int down_key, int left_key, int right_key) : Character(l, de, sprite_index, xpos, ypos, lives, up_key, down_key, left_key, right_key)
{
    spellKey = spellK;
    setClassID(MAGE_CLASSID);
}

bool Mage::__isKeyPressExecuteAction(int key)
{
    if (!Character::__isKeyPressExecuteAction(key))
        if (key == spellKey)
            return castSpell();
    
    return false;
}

bool Mage::castSpell()
{
    Fireball *temp = new Fireball(level, drawArea, SPRITE_FIREBALL, (int)getX()+facingDirection.x, (int)getY()+facingDirection.y, facingDirection.x, facingDirection.y);
    
    level->addNPC((Sprite *)temp);
    
    ++(level->numFireballs);
    
    return true;
}