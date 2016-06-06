//
//  bomb.hpp
//  evil-monkeys
//
//  Created by phuong on 5/15/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef bomb_h
#define bomb_h

#include "sprite.h"

namespace Target {

    using namespace EvilMonkeys;

    class Bomb : public Sprite
    {
    protected:
        void __idleUpdate(void);

    public:
        Bomb(DrawEngine *de, int sprite_index, float xpos, float ypos
             , int i_lives = 1)
        : Sprite(de, sprite_index, xpos, ypos, i_lives)
        {
            setClassID(BOMB_CLASSID);
        }
    };
}

#endif /* bomb_h */
