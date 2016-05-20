//
//  enemy.h
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef enemy_h
#define enemy_h

#include "sprite.h"

namespace EvilMonkeys
{
    class Character;

    class Enemy : public Sprite
    {
    public:
        Enemy(DrawEngine *de, int sprite_index, float xpos, float ypos, int i_lives = 1);
        
        inline void addGoal(Character* g){ goal = g; }
        
    private:
        
        bool __move(float xDir, float yDir);
        
        void __idleUpdate(void);
        
        void simulateAI_(void);
        
        Character* goal = NULL;
    };
}
#endif /* enemy_h */
