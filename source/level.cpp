//
//  level.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "level.hpp"

#include "character.hpp" // work around circular include header
#include "enemy.hpp"
#include "bomb.hpp"

using namespace EvilMonkeys;

#include <iostream>

Level::Level(DrawEngine *de, int w, int h)
{
    drawArea = de;
    
    isRunning = false;
    
    width = w;
    height = h;
    
    startTime = 0;
    elapsedTime = 0;
    
    player = 0;
    numEnemies = 0;
    numFireballs = 0;
    numBombs = 0;
    maxBombsAllow = 3;
    
    drawArea->setMap(createLevel(), width, height);
}

Level::~Level()
{
    delete player;
    
    // del memeory for level
    for (int x; x < width; x++)
        delete [] level[x];
    
    delete [] level;
    
    for (Iter = npc.begin(); Iter != npc.end(); Iter++)
        delete (*Iter);
}

int** const Level::createLevel()
{
    if (level != NULL)
        return level;
    
    // char ** ; create memory for our level
    level = new int *[width];
    
    for (int x = 0; x < width; x++)
        level[x] = new int[height];
    
    for (int x = 0; x < width - 2; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int random = rand() % 100;
            
            if (y == 0 || y == height - 2 || x == 0 || x == width - 3)
            {
                level[x][y] = TILE_WALL;
            }
            else
            {
                if (random < 88 || (x < 3 && y < 3))
                    level[x][y] = TILE_EMPTY;
                else
                    level[x][y] = TILE_WALL;
            }
            
        }
    }
    
    return level;
}

bool Level::isKeyPressExecuteAction(int key)
{
    if (getenv ("ESCDELAY") == NULL)
        ESCDELAY = 25;
    
    if (key == 27) {
        isRunning = !isRunning;
        return false;
    }        
    
    if (player->getLives() > 0)
        if (player->__isKeyPressExecuteAction(key))
            return true;
    
    return false;
}

void Level::update(unsigned long timing)
{
    if (startTime == 0) {
        startTime = timing;
    }
    
    elapsedTime = timing - startTime;
    
    std::string s = std::to_string(elapsedTime/1000);
    char const * tmp = s.c_str();
    
    drawArea->printScore(tmp, 1);
    drawArea->printScore("secs", 4);
    
    s = std::to_string(numEnemies);
    tmp = s.c_str();
    if (numEnemies > 9) {
        drawArea->printScore(tmp, 11);
        drawArea->printScore("enemies", 14);
    } else {
        drawArea->printScore(" ", 11);
        drawArea->printScore(tmp, 12);
        drawArea->printScore("enemies", 14);
    }
    s = std::to_string(player->getLives());
    tmp = s.c_str();
    
    drawArea->printScore(tmp, 22);
    drawArea->printScore(" lives", 23);
    
    s = std::to_string(maxBombsAllow - numBombs);
    tmp = s.c_str();
    
    if (maxBombsAllow - numBombs > 9) {
        drawArea->printScore(tmp, 31);
        drawArea->printScore("bombs left", 33);
    } else {
        drawArea->printScore(" ", 31);
        drawArea->printScore(tmp, 32);
        drawArea->printScore("bombs left", 33);
    }
    
    drawArea->printScore("running", 72);
    
    // simulate AI
    for (Iter = npc.begin(); Iter != npc.end(); Iter++) {
        
        (*Iter)->__idleUpdate();
        
        if ((*Iter)->getLives() < 1) {
            
            Sprite *temp = *Iter;
            
            Iter--;
            
            delete temp;
            
            npc.remove(temp);
        }
    }
}


void Level::addEnemies(int num)
{
    int i = num;
    
    while (i > 0)
    {
        int xpos = int((float(rand() % 100) / 100) * (width - 4) + 1);
        int ypos = int((float(rand() % 100) / 100) * (height - 4) + 1);
        
        if ( level[xpos][ypos] != TILE_WALL && xpos > player->getX() + 9 && ypos > player->getY() + 9 ) {
            
            // have to clean up those died enemy got killed to free memory somewhere!!!
            Enemy *temp = new Enemy(this, drawArea, SPRITE_ENEMY, (float)xpos, float(ypos));
            
            temp->addGoal(player);
            
            addNPC((Sprite *)temp);
            numEnemies++;
            i--;
        }
    }
}

void Level::spawnBombs(int num)
{
    maxBombsAllow = num;
    
    int i = num;
    
    while (i > 0) {
        int xpos = int((float(rand() % 100) / 100) * (width - 4) + 1);
        int ypos = int((float(rand() % 100) / 100) * (height - 4) + 1);
        
        typename std::list<Sprite *>::const_iterator Iter = npc.begin();
        typename std::list<Sprite *>::const_iterator itEnd = npc.end();
        
        bool flag = true;
        
        for( ; Iter != itEnd; ++Iter )
        {
            if (
                (int)(*Iter)->getX() == xpos &&
                (int)(*Iter)->getY() == ypos
                )
            {
                flag = false;
            }
        
        }
        
        if (level[xpos][ypos] != TILE_WALL && flag && xpos > player->getX() + 1 && ypos > player->getY() + 1) {
            
            // have to clean up those died bomb
            Bomb* temp = new Bomb(this, drawArea, SPRITE_BOMB, (float)xpos, (float)ypos);
            
            addNPC((Sprite *)temp);
            
            numBombs++;
            
            i--;
        }
    }
}