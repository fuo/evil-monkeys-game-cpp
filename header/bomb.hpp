//
//  bomb.hpp
//  evil-monkeys
//
//  Created by phuong on 5/15/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef bomb_hpp
#define bomb_hpp

#include "sprite.hpp"

namespace EvilMonkeys {
    class Bomb : public Sprite
    {
    public:
        Bomb(Level *lvl, DrawEngine *de, int sprite_index, float xpos, float ypos, int i_lives = 1);
        
    private:
        
        void __idleUpdate(void);
    };
}

#endif /* bomb_hpp */
