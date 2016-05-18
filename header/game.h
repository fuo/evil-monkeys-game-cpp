//
//  game.h
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef game_h
#define game_h

#include "drawEngine.h"

namespace EvilMonkeys
{
    class Game
    {
    public:
        void run(void);
        
    protected:
        void timerUpdate(double& lastTime);
        
    private:
        // incorperate the DrawEngine
        DrawEngine drawArea;

    };    
}
#endif /* game_h */