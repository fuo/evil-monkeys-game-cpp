//
//  level.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "level.h"

#include "fireball.h"
#include "enemy.h"
using namespace EvilMonkeys;

#include <iostream>
#include <math.h>

Level::Level(DrawEngine *de, int tile_wall, int w, int h)
{
    drawArea = de;
    
    running = false;
    
    width = w;
    height = h;
    
    startTime = 0;
    elapsedTime = 0;

    maxBombsAllow = 0;
    numBombs = 0;

    player = nullptr;

    setMapTile_(tile_wall);
    draw_( generatedMap_() );
}

Level::~Level()
{
    delete player;
    
    // del memeory for the created digital map
    for (int x; x < width; x++)
        delete [] digitalMap[x];
    
    delete [] digitalMap;
    
    for (sprite_Iter = NPC_sprites.begin(); sprite_Iter != NPC_sprites.end(); sprite_Iter++)
        delete (*sprite_Iter);
}

int** const Level::generatedMap_()
{
    if (digitalMap != NULL)
        return digitalMap;
    
    // create memory for our digital map
    digitalMap = new int *[width];
    
    for (int x = 0; x < width; x++)
        digitalMap[x] = new int[height];
    
    for (int x = 0; x < width - 2; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int random = rand() % 100;
            
            if (y == 0 || y == height - 2 || x == 0 || x == width - 3)
            {
                digitalMap[x][y] = TILE_WALL;
            }
            else
            {
                if (random < 88 || (x < 3 && y < 3))
                    digitalMap[x][y] = TILE_EMPTY;
                else
                    digitalMap[x][y] = TILE_WALL;
            }
            
        }
    }
    
    return digitalMap;
}

void Level::setMapTile_(int wall)
{
    drawArea->createBackgroundTile_(TILE_WALL, wall);
    drawArea->createBackgroundTile_(TILE_EMPTY, ' ');
}

void Level::draw_(int** const generatedMap)
{
    drawArea->setMap_(generatedMap, width, height);
    drawArea->drawBackground_();
}

bool Level::isKeyPressExecuteAction(int key)
{
    if (getenv ("ESCDELAY") == NULL)
        ESCDELAY = 25;
    
    if (key == 27) {
        running = !running;
        return false;
    }        
    
    if (player->getLives() > 0)
        if (player->__isKeyPressExecuteAction(key)){
            running = true;
            return true;
        }
    
    return false;
}

void Level::refreshStatuses_()
{
    int no_of_enemies = 0;
    int no_of_bombs = 0;


    typename std::list<Sprite *>::const_iterator Iter = NPC_sprites.begin();
    typename std::list<Sprite *>::const_iterator itEnd = NPC_sprites.end();

    for( ; Iter != itEnd; ++Iter )
    {
        switch ( (*Iter)->getClassID() ) {
            case ENEMY_CLASSID:
                no_of_enemies++;
                break;

            case BOMB_CLASSID:
                no_of_bombs++;
                break;

            default:
                break;
        }
    }

    std::string tmp = std::to_string(no_of_enemies);

    if (no_of_enemies > 9) {
        drawArea->printScore(tmp.c_str(), 11);
        drawArea->printScore("enemy", 15);
    } else {
        drawArea->printScore(" ", 11);
        drawArea->printScore(tmp.c_str(), 12);
        drawArea->printScore("enemy", 14);
    }

    tmp = std::to_string(player->getLives());

    drawArea->printScore(tmp.c_str(), 22);
    drawArea->printScore(" lives", 23);

    tmp = std::to_string(maxBombsAllow - numBombs);

    if (maxBombsAllow - numBombs > 9) {
        drawArea->printScore(tmp.c_str(), 31);
        drawArea->printScore("bombs", 34);
    } else {
        drawArea->printScore(" ", 31);
        drawArea->printScore(tmp.c_str(), 32);
        drawArea->printScore("bombs", 34);
    }

    tmp = std::to_string(no_of_bombs);
    drawArea->printScore(tmp.c_str(), 42);
    drawArea->printScore("bombs avail", 44);
}

void Level::update(unsigned long timing)
{
    if (startTime == 0)
        startTime = timing;
    
    elapsedTime = timing - startTime;
    
    std::string seconds = std::to_string(elapsedTime/1000);
    
    drawArea->printScore(seconds.c_str(), 1);
    drawArea->printScore("secs", 4);

    refreshStatuses_();

    drawArea->printScore("running", 72);
    
    // simulate all NPC while idle time
    for (sprite_Iter = NPC_sprites.begin(); sprite_Iter != NPC_sprites.end(); sprite_Iter++) {
        
        (*sprite_Iter)->__idleUpdate();
        
        if ((*sprite_Iter)->getLives() < 1) {
            
            removeNPC(*sprite_Iter--);

        }
    }
}

bool Level::checkMapTileEmpty(int xpos, int ypos)
{
    if ( xpos > width || xpos < 0 || ypos > height || ypos < 0 )
        return false;

    return digitalMap[xpos][ypos] == TILE_EMPTY;
}

        return false;



bool Level::spawnNPC(int sprite_index, int distanceToGoal, int xpos, int ypos, float xface, float yface)
{
    switch (sprite_index) {
        case SPRITE_ENEMY:
            return spawnEnemies_(sprite_index, distanceToGoal, xpos, ypos);

        case SPRITE_BOMB:
            return spawnBombs_(sprite_index, distanceToGoal, xpos, ypos);

        case SPRITE_FIREBALL:
        default:
            break;
    }

    return false;
}

}

{
    if (xpos == -1)
    {
    }

    if (ypos == -1)
    {
    }





    }
}