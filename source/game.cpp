//
//  game.cpp
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "game.h"

#include "drawEngine.h"
#include "character.h"

#include <ncurses.h>
#include <sys/time.h>

#define GAME_SPEED 50

bool kbhit(void);
bool getKeyInput(int& key);

void EvilMonkeys::Game::run(DrawEngine* drawArea)
{
    //setup
    int playerSprite = drawArea->createSprite(0, 'o', RED_BLACK);

    Character* hero = new Character(drawArea, playerSprite);

    double lastTime = 0;
    int key = ' ';
    
    nodelay(stdscr, TRUE);
    
    while (key != 'q')
    {
        while (!getKeyInput(key))
        {

            this->timerUpdate_(lastTime);
            
            // constantly refresh the windows
            drawArea->refresh();
        }
        
        // pass the pressed key to the level
        
        hero->__isKeyPressExecuteAction(key);

    }
    
}

void EvilMonkeys::Game::timerUpdate_(double & lastTime)
{
    timeval* tv = new timeval();
    gettimeofday(tv, 0);
    
    double currentTime = (tv->tv_sec + double(tv->tv_usec)/1000000.0)*1000 - lastTime;
    
    if (currentTime < GAME_SPEED)
        return;
    
    //----------------------------------

    // this is for NPC not our hero
    
    //----------------------------------
    
    gettimeofday(tv, 0);
    lastTime = (tv->tv_sec + double(tv->tv_usec)/1000000.0)*1000;
}


bool getKeyInput(int & key)
{
    if (kbhit())
    {
        key = getch();
        return true;
    }
    
    return false;
}

bool kbhit()
{
    int ch = getch();
    
    if (ch != ERR)
    {
        ungetch(ch);
        return true;
    }
    
    return false;
}