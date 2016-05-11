//
//  mage.cpp
//  3dbuzz
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include <iostream>


#include "mage.hpp"
#include "fireball.hpp"

using namespace std;

Mage::Mage(Level *l, DrawEngine *de, int s_index, float x, float y,
           int lives, char spellK, int up_key, int down_key, int left_key, int right_key) : Character(l, de, s_index, x, y, lives, up_key, down_key, left_key, right_key)
{
    spellKey = spellK;
    classID = MAGE_CLASSID;
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
    
    
    Fireball *temp = new Fireball(level, drawArea, SPRITE_FIREWALL, (int)pos.x+facingDirection.x, (int)pos.y+facingDirection.y, facingDirection.x, facingDirection.y);
    
    level->addNPC((Sprite *)temp);
    
}