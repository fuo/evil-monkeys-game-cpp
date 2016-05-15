//
//  mage.h
//  Evil Monkey Game
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef mage_h
#define mage_h

#include "character.hpp"

namespace EvilMonkeys
{
    class Mage : public Character
    {
    public:
        Mage(Level *l, DrawEngine *de, int sprite_index, float xpos = 1, float ypos = 1,
             int lives = 3, char spellKey = ' ', char bombKey = 'x', int up_key = KEY_UP, int down_key = KEY_DOWN, int left_key = KEY_LEFT, int right_key = KEY_RIGHT);
        
    private:
        char spellKey, bombKey;
        
        // thanks virtual, the keypress in parent is public, so this one can be hidden!
        bool __isKeyPressExecuteAction(int key);
        
        bool castSpell(void);
        
        bool castBomb(void);
    };
}
#endif /* mage_h */
