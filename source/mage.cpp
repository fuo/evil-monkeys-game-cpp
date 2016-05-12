//
//  mage.cpp
//  3dbuzz
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "mage.hpp"

#include "level.hpp"
#include "fireball.hpp"

Mage::Mage(Level *l, DrawEngine *de, int s_index, float x, float y,
           int lives, char spellK, int up_key, int down_key, int left_key, int right_key) : Character(l, de, s_index, x, y, lives, up_key, down_key, left_key, right_key)
{
    spellKey = spellK;
    setClassID(MAGE_CLASSID);
}

bool Mage::keyPress(int c)
{
    
    
    
    bool val = Character::keyPress(c);
    
    if (val == false) {
        
        
        if (c == spellKey) {
            
            
            
            castSpell();
            return true;
        }
    }
    
    return val;
}

void Mage::castSpell(){
    
    
    Fireball *temp = new Fireball(level, drawArea, SPRITE_FIREBALL, (int)getX()+facingDirection.x, (int)getY()+facingDirection.y, facingDirection.x, facingDirection.y);
    
    level->addNPC((Sprite *)temp);
    
}