//
//  fireball.h
//  3dbuzz
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef fireball_h
#define fireball_h

#include "sprite.hpp"

class Fireball : public Sprite
{
public:
    Fireball(Level *lev, DrawEngine *de, int s_index, float x = 1, float y = 1,
             float xDir = 0, float yDir = 0, int i_lives = 1);
    
    void idleUpdate(void);
    
    
};

#endif /* fireball_h */
