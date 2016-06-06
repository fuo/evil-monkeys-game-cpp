//
//  game.h
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef game_h
#define game_h


#define GAME_SPEED 50
#define KEY_QUIT_GAME 'q'

#define NUM_ENEMY 1
#define NUM_BOMB 10
#include "level.h"

namespace EvilMonkeys
{
    typedef Concern::Counting_Aspect<Target::Bomb> Bomb;
    typedef Concern::Counting_Aspect<Target::Fireball> Fireball;
    typedef Concern::Counting_Aspect<Target::Mage> Mage;
    class DrawEngine;
    class Level;

    class Game
    {
    public:
        void run(DrawEngine* drawArea);
        
    protected:
        void timerUpdate_(double& lastTime);

    private:
        Level* world;

    };    
}
#endif /* game_h */