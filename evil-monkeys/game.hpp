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

class Sprite;

class Game
{
public:
    Game(){}
    ~Game(){}
    
    void run(void);
    
protected:
    void timerUpdate(double & lastTime);
    
private:
    DrawEngine drawArea;
    Sprite* player;
//    Level level;
    
};

#endif /* game_hpp */
