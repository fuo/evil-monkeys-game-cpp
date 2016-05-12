//
//  game.hpp
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include "drawEngine.hpp"

class Level;

class Game
{
public:
    void run(void);
    
protected:
    void timerUpdate(double& lastTime);
    
private:
    DrawEngine drawArea;
    Level* level;
    
};

#endif /* game_hpp */
