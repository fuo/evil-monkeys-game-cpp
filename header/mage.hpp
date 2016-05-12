//
//  mage.h
//  3dbuzz
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef mage_h
#define mage_h

#include "character.hpp"

class Mage : public Character
{
public:
    Mage(Level *l, DrawEngine *de, int s_index, float x = 1, float y = 1,
         int lives = 3, char spellKey = ' ', int up_key = KEY_UP, int down_key = KEY_DOWN, int left_key = KEY_LEFT, int right_key = KEY_RIGHT);
    
    bool keyPress(int c);
    
protected:
    void castSpell(void);
    
private:
    char spellKey;
};

#endif /* mage_h */
