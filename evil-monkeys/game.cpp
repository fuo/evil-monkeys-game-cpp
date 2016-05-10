//
//  game.cpp
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//
#include "game.hpp"

#include <sys/time.h>
#include <ncurses.h>

#define GAME_SPEED 50

int kbhit(void);
bool getKeyInput(char&);

void Game::run()
{
    double lastTime = 0;
    char key = ' ';
    nodelay(stdscr, TRUE);
    while (key != 'q') {
        while (!getKeyInput(key)) {
            this->timerUpdate(lastTime);
        }
        // pass the pressed key to the level
    }

//    int ch;
//    nodelay(stdscr, TRUE);
//    for (;;) {
//        if ((ch = getch()) == ERR) {
//            /* user hasn't responded
//             ...
//             */
//        }
//        else {
//            /* user has pressed a key ch
//             ...
//             */
//        }
//    }
    
}
int i = 0;
void Game::timerUpdate(double & lastTime)
{
    timeval* tv = new timeval();
    gettimeofday(tv, 0);
    
    double currentTime = (tv->tv_sec + double(tv->tv_usec)/1000000.0)*1000 - lastTime;
    
    if (currentTime < GAME_SPEED) {
        return;
    }
    
    // level update automatically
    
//    printw("fafa afas");
    
    drawArea.createSprite(0, '*');
    drawArea.drawSprite(0, ++i, 1);
    
    gettimeofday(tv, 0);
    lastTime = (tv->tv_sec + double(tv->tv_usec)/1000000.0)*1000;
}


bool getKeyInput(char & key)
{
    if (kbhit()) {
        key = getch();
        
        return true;
    }
    
    return false;
}

int kbhit()
{
    int ch = getch();
    
    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}