//
//  fireball.h
//  Evil Monkey Game
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef fireball_h
#define fireball_h

#include "bomb.hpp"

namespace EvilMonkeys
{
    class Fireball : public Bomb
    {
    public:
        Fireball(Level *lvl, DrawEngine *de, int sprite_index, float xpos, float ypos,
                 float xDir, float yDir, int i_lives = 1);
     
    private:
        
        void __idleUpdate(void);
        
    };
}
#endif /* fireball_h */
