//
//  game.hpp
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <ncurses.h>

class Game
{
public:
    Game(void);
    ~Game(void);
    
    void run(void);
    
protected:
    void timerUpdate(double & lastTime);
    
private:
    
};

#endif /* game_hpp */
