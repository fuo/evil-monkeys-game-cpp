//
//  character.h
//  evil-monkeys
//
//  Created by phuong on 5/11/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef character_h
#define character_h

#include "sprite.h"
#include <ncurses.h>

namespace EvilMonkeys
{
    class Character : public Sprite
    {
    public:
        Character(DrawEngine *de, int sprite_index, float sprite_xpos = 1, float sprite_ypos = 1, int sprite_lives = 3,
                  int character_upKey = KEY_UP, int character_downKey = KEY_DOWN,
                  int character_leftKey = KEY_LEFT, int character_rightKey = KEY_RIGHT);
        
        virtual bool __isKeyPressExecuteAction(int i_key);
        
        void __addLives(int num = 1);
        
    protected:
        int i_upKey, i_downKey, i_rightKey, i_leftKey;
        
    private:
        bool __move(float xDir, float yDir);
        void __hookToLevel(Level* lvl, bool draw_at_once = true);
    };
}
#endif /* character_h */
