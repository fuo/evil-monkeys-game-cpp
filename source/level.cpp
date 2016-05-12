//
//  level.cpp
//  3dbuzz
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "level.hpp"

#include "character.hpp" // work around circular include header
#include "enemy.hpp"

#include <stdlib.h>
#include <iostream>
using namespace std;

Level::Level(DrawEngine *de, int w, int h)
{
    drawArea = de;
    
    width = w;
    height = h;
    
    player = 0;
    numEnemies = 0;
    
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

char** const Level::createLevel()
{
    if (level != NULL)
        return level;
    
    // char ** ; create memory for our level
    level = new char *[width];
    
    for (int x = 0; x < width; x++)
        level[x] = new char[height];
    
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
                if (random < 90 || (x < 3 && y < 3))
                    level[x][y] = TILE_EMPTY;
                else
                    level[x][y] = TILE_WALL;
            }
            
        }
    }
    
    return level;
}

bool Level::keyPress(int key)
{
    if (player->getLives() > 0)
        if (player->keyPress(key))
            return true;
    
    return false;
}

void Level::update()
{
    drawArea->printScore(1, 1, "Level 1: ");
    
    string s = to_string(numEnemies);
    char const * tmp = s.c_str();
    
    drawArea->printScore(11, 1, tmp);
    drawArea->printScore(12, 1, " enemies");
    
    s = to_string(player->getLives());
    tmp = s.c_str();
    
    drawArea->printScore(22, 1, tmp);
    drawArea->printScore(23, 1, " lives");
    
    
    // simulate AI
    for (Iter = npc.begin(); Iter != npc.end(); Iter++) {
        
        (*Iter)->idleUpdate();
        
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
    
    while (i > 0) {
        int xpos = int((float(rand() % 100) / 100) * (width - 2) + 1);
        int ypos = int((float(rand() % 100) / 100) * (height - 2) + 1);
        
        if (level[xpos][ypos] != TILE_WALL) {
            
            // have to clean up those died enemy got killed to free memory somewhere!!!
            Enemy *temp = new Enemy(this, drawArea, SPRITE_ENEMY, (float)xpos, float(ypos));
            
            temp->addGoal(player);
            
            addNPC((Sprite *)temp);
            numEnemies++;
            i--;
        }
    }
}