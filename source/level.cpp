//
//  level.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "game.h"

#include "level.h"

using namespace EvilMonkeys;

Level::Level(DrawEngine *de, int wallTile, int w, int h)
: drawArea_{de}
, running_{false}
, width_{w}
, height_{h}
, startTime_{0}
, elapsedTime_{0}
, lastTimeReload_{0}
, maxBombsAllow_{0}
, numBombs_{0}
, player_{nullptr}
{
    setMapTile_(wallTile);
    draw_( generatedDigitalMap_(100 - CHANCE_OF_EMPTY_TILE) );
}

Level::~Level()
{
    // del memeory for the created digital map
    for (int x; x < width_; x++)
        delete [] digitalMap_[x];
    
    delete [] digitalMap_;

    for (auto& sprite_Iter : NPC_sprites_)
        delete sprite_Iter;
}



int** const Level::generatedDigitalMap_(int wall_density)
{
    if (digitalMap_ != NULL)
        return digitalMap_;
    
    // create memory for our digital map
    digitalMap_ = new int *[width_];
    
    for (int x = 0; x < width_; x++)
        digitalMap_[x] = new int[height_];
    
    for (int x = 0; x < width_ - 2; x++)
        for (int y = 0; y < height_; y++)
        {
            int random = rand() % 100;
            
            if (y == 0 || y == height_ - 2 || x == 0 || x == width_ - 3)
            {
                digitalMap_[x][y] = TILE_WALL;
            }
            else
            {
                if (random < 100 - wall_density || (x < 3 && y < 3))
                    digitalMap_[x][y] = TILE_EMPTY;
                else
                    digitalMap_[x][y] = TILE_WALL;
            }
            
        }
    
    return digitalMap_;
}

void Level::setMapTile_(int wall)
{
    drawArea_->createBackgroundTile_(TILE_WALL, wall);
    drawArea_->createBackgroundTile_(TILE_EMPTY, EMPTY_CHAR);
}

void Level::draw_(int** const generatedMap)
{
    drawArea_->setMap_(generatedMap,width_, height_);
    drawArea_->drawBackground_();
}

bool Level::isKeyPressExecuteAction(int key)
{
    if (getenv ("ESCDELAY") == NULL)
        ESCDELAY = 25;

    if (key == ESC_KEY) {
        running_ = !running_;
        return false;
    }        
    
    if (player_->getLives() > 0)
        if (player_->__isKeyPressExecuteAction(key)){
            running_ = true;
            return true;
        }
    
    return false;
}

void Level::refreshStatuses_()
{
    int no_of_enemies = 0;
    int no_of_bombs = 0;

    for( auto& Iter : NPC_sprites_ )
    {
        switch ( Iter->getClassID() ) {
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
        drawArea_->printScore(tmp.c_str(), 11);
        drawArea_->printScore("enemy", 15);
    } else {
        drawArea_->printScore(" ", 11);
        drawArea_->printScore(tmp.c_str(), 12);
        drawArea_->printScore("enemy", 14);
    }

    tmp = std::to_string(player_->getLives());

    drawArea_->printScore(tmp.c_str(), 22);
    drawArea_->printScore(" lives", 23);

    tmp = std::to_string(maxBombsAllow_ - numBombs_);

    if (maxBombsAllow_ - numBombs_ > 9) {
        drawArea_->printScore(tmp.c_str(), 31);
        drawArea_->printScore("bombs", 34);
    } else {
        drawArea_->printScore(" ", 31);
        drawArea_->printScore(tmp.c_str(), 32);
        drawArea_->printScore("bombs", 34);
    }

    tmp = std::to_string(no_of_bombs);
    if (no_of_bombs > 9) {
        drawArea_->printScore(tmp.c_str(), 42);
        drawArea_->printScore("bombs avail", 44);
    } else{
        drawArea_->printScore(" ", 42);
        drawArea_->printScore(tmp.c_str(), 43);
        drawArea_->printScore("bombs avail", 44);
    }

    tmp = std::to_string(((Mage*)player_)->getAmmoCartridge());
    drawArea_->printScore(tmp.c_str(), 60);
    drawArea_->printScore("ammo", 62);
}

void Level::update(unsigned long timing)
{
    if (startTime_ == 0)
        startTime_ = timing;
    
    elapsedTime_ = timing - startTime_;
    
    std::string seconds = std::to_string(elapsedTime_/1000);
    
    drawArea_->printScore(seconds.c_str(), 1);
    drawArea_->printScore("secs", 4);

    refreshStatuses_();

    drawArea_->printScore("running", 72);
    
    // simulate all NPC while idle time
    for (auto sprite_Iter = begin(NPC_sprites_); sprite_Iter != end(NPC_sprites_); sprite_Iter++)
    {
        (*sprite_Iter)->__idleUpdate();
        
        if ((*sprite_Iter)->getLives() < 1)
            removeNPC(*sprite_Iter--);
    }
}

bool Level::checkMapTileEmpty(int xpos, int ypos, int excludeSpriteIndex)
{
    if (excludeSpriteIndex == SPRITE_PLAYER)
        return !player_->matchCurrentLocation(xpos, ypos);

    if ( xpos > width_ || xpos < 0 || ypos > height_ || ypos < 0)
        return false;

    int excludeSpriteCLASSID = excludeSpriteIndex;

    switch (excludeSpriteIndex) {
        case SPRITE_BOMB:
            excludeSpriteCLASSID = BOMB_CLASSID;
            break;

        case SPRITE_ENEMY:
            excludeSpriteCLASSID = ENEMY_CLASSID;
            break;

        default:
            excludeSpriteCLASSID = excludeSpriteIndex;
            break;
    }

    if ( excludeSpriteCLASSID >= 0 )
        for( auto& Iter : NPC_sprites_ )
            if ( Iter->matchCurrentLocation(xpos, ypos) && Iter->is(excludeSpriteCLASSID) )
                return false;

    return digitalMap_[xpos][ypos] == TILE_EMPTY;
}

bool Level::spawnNPC(int sprite_index, int distanceToGoal, int xpos, int ypos, float xface, float yface)
{
    if (xpos == -1)
    {
        if (ypos != -1)
            do { xpos = gen_xpos(width_); }
            while ( !checkMapTileEmpty(xpos, ypos, sprite_index) || !player_->checkSafeSpawnPosition(xpos, ypos, distanceToGoal) );
        else
            do { xpos = gen_xpos(width_); ypos = gen_ypos(height_); }
            while ( !checkMapTileEmpty(xpos, ypos, sprite_index) || !player_->checkSafeSpawnPosition(xpos, ypos, distanceToGoal) );
    }

    if (ypos == -1)
    {
        if(xpos != -1)
            do { ypos = gen_ypos(height_); }
            while ( !checkMapTileEmpty(xpos, ypos, sprite_index) || !player_->checkSafeSpawnPosition(xpos, ypos, distanceToGoal) );
        else
            do { xpos = gen_xpos(width_); ypos = gen_ypos(height_); }
            while ( !checkMapTileEmpty(xpos, ypos, sprite_index) || !player_->checkSafeSpawnPosition(xpos, ypos, distanceToGoal) );
    }

    if ( !checkMapTileEmpty(xpos, ypos, sprite_index) || !player_->checkSafeSpawnPosition(xpos, ypos, distanceToGoal) )
        return false;

    Sprite* temp;

    switch (sprite_index) {
        case SPRITE_ENEMY:
            temp = new Enemy(drawArea_, sprite_index, (float)xpos, float(ypos));
            break;

        case SPRITE_BOMB:
            temp = new Bomb(drawArea_, sprite_index, (float)xpos, (float)ypos);
            break;

        case SPRITE_FIREBALL:
            temp = new Fireball(drawArea_, sprite_index, float(xpos - xface), float(ypos - yface), xface, yface);
            break;

        default:
            return false;
    }

    return temp->__hookToLevel(this);
}