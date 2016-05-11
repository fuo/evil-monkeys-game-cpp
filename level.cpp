//
//  level.cpp
//  evil-monkeys
//
//  Created by phuong on 5/11/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "level.hpp"

#include <iostream>
using namespace std;

#include <sys/time.h>

#include "character.hpp"
#include "enemy.hpp"

#include <stdlib.h>

Level::~Level(){
    // del memeory for level
    for (int x; x < width; x++)
        delete [] level[x];
    
    delete [] level;
    
    for (Iter = npc.begin(); Iter != npc.end(); Iter++)
        delete (*Iter);
}

Level::Level(DrawEngine *de, int w, int h)
{
    drawArea = de;
    
    width = w;
    height = h;
    
    player = NULL;
    
    // char ** ; create memory for our level
    level = new char* [width];
    for (int x = 0; x < width; x++)
        level[x] = new char[height];
    
    create();
    
//    mvwprintw(score, 1, 1, "Score");
    
    
//    drawArea->printScore(8, 1, &"" [ width]);
    
    drawArea->setMap(level, width, height);
    
    drawArea->createBackgroundTile(TILE_EMPTY, ' ');
    drawArea->createBackgroundTile(TILE_WALL, 219);
    
    
    drawArea->createSprite(SPRITE_ENEMY, '$');
//    drawArea->createSprite(SPRITE_FIREWALL, '*');
    
    draw();
}

void Level::create()
{
    for (int x = 0; x < width - 2; x++) {
        for (int y = 0; y < height; y++) {
            
            int random = rand() % 100;
            
            
            
            if (y == 0 || y == height - 2 || x == 0 || x == width - 3)
            {
                
                level[x][y] = TILE_WALL;
            }
            else
            {
                
                if (random < 90 || (x < 3 && y < 3)) {
                    level[x][y] = TILE_EMPTY;
                }else{
                    level[x][y] = TILE_WALL;
                }
            }
            
        }
    }
}

//void Level::create()
//{
//    for (int x = 0; x < width - 2; x++) {
//        for (int y = 1; y < height - 1; y++) {
//            
//            int random = rand() % 100;
//            
//            
//            
//            if (y == 1 || y == height - 2 || x == 0 || x == width - 3)
//            {
//                
//                level[x][y] = TILE_WALL;
//            }
//            else
//            {
//                
//                if (random < 90 || (x < 3 && y < 3)) {
//                    level[x][y] = TILE_EMPTY;
//                }else{
//                    level[x][y] = TILE_WALL;
//                }
//            }
//            
//        }
//    }
//}


void Level::draw()
{
    // draw the background of level
    drawArea->drawBackground();
}

bool Level::addPlayer(Character *p, int xpos, int ypos)
{
    player = p;
    // player->move(xpos, ypos);
    //addEnemies(num_of_enemies);
    
    return true;
}

bool Level::keyPress(int c)
{
    if (player)
        if (player->keyPress(c))
            return true;
    
    
    return false;
}

void Level::update(){
    
    
    
    string s = to_string(width);
    char const * tmp = s.c_str();
    
    drawArea->printScore(5, 1, tmp);
    
    s = to_string(height);
    tmp = s.c_str();
    
    drawArea->printScore(8, 1, tmp);
    
    // simulate AI
    
    for (Iter = npc.begin(); Iter != npc.end(); Iter++) {
        
        Sprite* e = *Iter;
        
        (*Iter)->idleUpdate();
        
        if (!e->isAlive()) {
            
            Sprite *temp = *Iter;
            
            Iter--;
            
            npc.remove(temp);
            
            delete temp;
        }
    }
}


bool Level::addEnemies(int num)
{
    int i = num;
    
    while (i > 0) {
        
        timeval* tv = new timeval();
        gettimeofday(tv, 0);
        
        srand(tv->tv_sec + double(tv->tv_usec));
        
        double X = double(int(((double)rand()/(double)RAND_MAX) * 1000000) % 100) / 100;
        
        srand((unsigned)time(NULL));
        double Y = double(int(((double)rand()/(double)RAND_MAX) * 1000000) % 100) / 100;        
        
        int xpos = int(X * (width - 2 - 6) + 1);
        int ypos = int(Y * (height - 2 - 6) + 1);
        
        if (level[xpos][ypos] != TILE_WALL) {
            
            // have to clean up those died enemy got killed to free memory somewhere!!!
            Enemy *temp = new Enemy(this, drawArea, SPRITE_ENEMY, (float)xpos, float(ypos));
            
            nodelay(stdscr, FALSE);
            
            temp->addGoal(player);
            
//            temp->draw(xpos, ypos);
            
            addNPC((Sprite *)temp);
            
            --i;
        }
    }
    
    return true;
}

void Level::addNPC(Sprite *spr)
{
    npc.push_back(spr);
    
}