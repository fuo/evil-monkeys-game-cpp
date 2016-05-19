//
//  game.h
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef game_h
#define game_h

namespace EvilMonkeys
{
    class DrawEngine;

    class Game
    {
    public:
        void run(DrawEngine* drawArea);
        
    protected:
        void timerUpdate_(double& lastTime);
            
    };    
}
#endif /* game_h */