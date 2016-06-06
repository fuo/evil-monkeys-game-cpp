//
//  level.h
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef level_h
#define level_h

#include <memory>
#include <list>
#include <math.h>
#include <iostream>

#include "mage.h"
#include "fireball.h"
#include "enemy.h"

namespace EvilMonkeys
{
    #define PLAYER_CHAR '>'
    #define ENEMY_CHAR '$'
    #define BOMB_CHAR '*'

    #define WALL_CHAR ACS_CKBOARD | A_REVERSE
    #define EMPTY_CHAR ' '

    #define LEVEL_WIDTH 80
    #define LEVEL_HEIGHT 21

    #define DISTANCE_TO_PLAYER 9
    #define ESC_KEY 21

    #define CHANCE_OF_EMPTY_TILE 88

    enum backgroundTile_ID
    {
        TILE_EMPTY,
        TILE_WALL
    };

    class Level
    {
        int width_;
        int height_;

        bool running_;

        int maxBombsAllow_, numBombs_;
        int numFireballs_;

        unsigned long startTime_;
        unsigned long elapsedTime_;

        unsigned long lastTimeReload_;
        std::list<Sprite *> NPC_sprites_;
        int** digitalMap_;

        // the first sprite that has isKeyPressExecuteAction method (the human control sprite index)
        Character *player_;
        
        DrawEngine *drawArea_;

    public:
        Level(DrawEngine *de, int tile_wall = WALL_CHAR, int width = LEVEL_WIDTH, int height = LEVEL_HEIGHT);
        ~Level();
        
        inline int getWidth(){ return width_; }
        inline int getHeight(){ return height_; }

        bool checkMapTileEmpty(int xpos, int ypos, int excludeSpriteCLASSID = -1);

        inline bool addPlayer(Character *p){ player_ = p; return player_ != nullptr; }
        
        inline Character* const player(){ return player_; }

        void update(unsigned long time);
        
        void setLastTimeReload(unsigned long time){ lastTimeReload_ = time; }
        unsigned long getLastTimeReload(){ return lastTimeReload_; }

        unsigned long getElapsedTime(){ return elapsedTime_; }

        bool isKeyPressExecuteAction(int key);

        inline int gen_xpos(int width){ return (int)lround((float(rand() % 100) / 100) * (width - 4) + 1); }
        inline int gen_ypos(int height){ return (int)lround((float(rand() % 100) / 100) * (height - 4) + 1); }

        inline bool isPaused(){ return !running_; }
        inline void pause(){ refreshStatuses_(); running_ = false; }

        auto const NPC(){ return NPC_sprites_; }

        bool spawnNPC(int sprite_index, int distanceToGoal = DISTANCE_TO_PLAYER, int xpos = -1, int ypos = -1, float xface = 0, float yface = 0);

        int getNumFireballs(){ return numFireballs_; }
        int getNumBombs(){ return numBombs_; }
        int getMaxBombsAllow(){ return maxBombsAllow_; }
        void updateNumBombs(int num){ numBombs_ += num; }
        void updateNumFireballs(int num){ numFireballs_ += num; }

        inline void addNPC(Sprite *spr){ NPC_sprites_.push_back(spr); }
        inline void removeNPC(Sprite* spr){ delete spr; NPC_sprites_.remove(spr); }

    protected:
        void setMapTile_(int wall);
        void draw_(int** const generatedMap);

        int** const generatedDigitalMap_(int wall_density);

    private:
        void refreshStatuses_(void);
    };

#include "countingAspect.h"

}
#endif /* level_h */
