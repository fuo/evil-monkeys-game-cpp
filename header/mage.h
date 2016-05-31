//
//  mage.h
//  Evil Monkey Game
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef mage_h
#define mage_h

#include "character.h"

#define FULL_AMMO 9
#define COOL_DOWN_RELOAD_IN_MILISECOND 500

namespace EvilMonkeys
{
    class Mage : public Character
    {
    public:
        Mage(DrawEngine *de, int sprite_index, float xpos = 1, float ypos = 1,
             int lives = 3, char spellKey = ' ', char reloadKey = 'r', char bombKey = 't', int up_key = KEY_UP, int down_key = KEY_DOWN, int left_key = KEY_LEFT, int right_key = KEY_RIGHT);

        void updateAmmoCartridge(int ammo){ ammoCartridge += ammo; }
        int getAmmoCartridge(void){ return ammoCartridge; }

    private:
        char spellKey, reloadKey, bombKey;

        int ammoCartridge = FULL_AMMO;

        // thanks virtual, the keypress in parent is public, so this one can be hidden!
        bool __isKeyPressExecuteAction(int key);

        bool castSpell_(void);
        bool reload_(void);
        bool castBomb_(void);
    };
}
#endif /* mage_h */
