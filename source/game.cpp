//
//  game.cpp
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "game.hpp"

#include "mage.hpp"
#include "level.hpp"

using namespace EvilMonkeys;

#include <sys/time.h>


#define GAME_SPEED 50

bool kbhit(void);
bool getKeyInput(int& key);

void Game::run()
{
    level = new Level(&drawArea, 80);
    
    drawArea.createBackgroundTile(TILE_EMPTY, ' ');
    drawArea.createBackgroundTile(TILE_WALL, 219);
    
    drawArea.createSprite(SPRITE_PLAYER, 'o');
    drawArea.createSprite(SPRITE_ENEMY, '$');
    drawArea.createSprite(SPRITE_FIREBALL, '*');
    
    level->draw();
    
    level->addPlayer(new Mage(level, &drawArea, SPRITE_PLAYER));
    level->addEnemies(3);
    
    double lastTime = 0;
    int key = ' ';
    
    nodelay(stdscr, TRUE);
    
    while (key != 'q')
    {
        while (!getKeyInput(key))
        {
            // constantly refresh the window
            drawArea.setup();
            
            this->timerUpdate(lastTime);
        }

        // pass the pressed key to the level
        level->keyPress(key);
    }
    
    delete level;
}

void Game::timerUpdate(double & lastTime)
{
    timeval* tv = new timeval();
    gettimeofday(tv, 0);
    
    double currentTime = (tv->tv_sec + double(tv->tv_usec)/1000000.0)*1000 - lastTime;
    
    if (currentTime < GAME_SPEED)
        return;
    
//----------------------------------
    
    level->update();
    
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