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

#include <sys/time.h>
#include <ncurses.h>

#define GAME_SPEED 50

int kbhit(void);
bool getKeyInput(int&);

void Game::run()
{
    level = new Level(&drawArea, 80);
    
    
    drawArea.createBackgroundTile(TILE_EMPTY, ' ');
    drawArea.createBackgroundTile(TILE_WALL, 219);
    
    drawArea.createSprite(SPRITE_PLAYER, 'o');
    drawArea.createSprite(SPRITE_ENEMY, '$');
    drawArea.createSprite(SPRITE_FIREWALL, '*');
    
    
    
    player = new Mage(level, &drawArea, SPRITE_PLAYER);
    
    level->draw();
    
    level->addPlayer(player);
    level->addEnemies(3);
    
    double lastTime = 0;
    int key = ' ';
    
    nodelay(stdscr, TRUE);
    
    while (key != 'q') {
        
        while (!getKeyInput(key)) {
            
             drawArea.setup();
            
            this->timerUpdate(lastTime);
        }
        // pass the pressed key to the level
//        player->keyPress(key);
        level->keyPress(key);
    }

    delete player;
    
}

void Game::timerUpdate(double & lastTime)
{
    timeval* tv = new timeval();
    gettimeofday(tv, 0);
    
    double currentTime = (tv->tv_sec + double(tv->tv_usec)/1000000.0)*1000 - lastTime;
    
    if (currentTime < GAME_SPEED) {
        return;
    }
    
    // level update automatically
    
    level->update();
    
//    player->move(1, 0);
//    drawArea.drawSprite(0, ++i, 1);
    
    gettimeofday(tv, 0);
    lastTime = (tv->tv_sec + double(tv->tv_usec)/1000000.0)*1000;
}


bool getKeyInput(int & key)
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


