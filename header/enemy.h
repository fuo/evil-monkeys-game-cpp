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
        Enemy(DrawEngine *de, int sprite_index, float xpos, float ypos, int i_lives = 2) : Sprite(de, sprite_index, xpos, ypos, i_lives)
        {
            setClassID(ENEMY_CLASSID);
        }

        inline void addGoal(Character* g){ goal = g; }

    protected:
        void __idleUpdate(void);

    private:
        bool __move(float xDir, float yDir);
        bool __hookToLevel(Level* lvl, bool draw_at_once = true);

        void __addLives(int num = 1);

        void simulateAI_(void);

        Character* goal = NULL;
    };
}
#endif /* enemy_h */
