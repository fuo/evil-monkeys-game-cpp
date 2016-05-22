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

namespace EvilMonkeys {
    class Bomb : public Sprite
    {
    public:
        Bomb(DrawEngine *de, int sprite_index, float xpos, float ypos, int i_lives = 1);
        
    protected:
        
        void __idleUpdate(void);
    };
}

#endif /* bomb_h */
