//
//  level.h
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef level_h
#define level_h

#include <list>

#include "drawEngine.h"
#include "character.h"

#include <math.h>
#include <iostream>

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

namespace EvilMonkeys
{
    enum sprite_ID
    {
        SPRITE_PLAYER,
        SPRITE_ENEMY,
        SPRITE_FIREBALL,
        SPRITE_BOMB,
        SPRITE_ENEMY_1,
    };

    enum backgroundTile_ID
    {
        TILE_EMPTY,
        TILE_WALL
    };

    class Level
    {
    public:
        Level(DrawEngine *de, int tile_wall = ACS_CKBOARD | A_REVERSE, int width = 80, int height = 21);
        ~Level();
        
        inline int getWidth(){ return width; }
        inline int getHeight(){ return height; }

        bool checkMapTileEmpty(int xpos, int ypos, int excludeSpriteCLASSID = -1);

        inline void addPlayer(Character *p){ player = p; }
        
        void update(unsigned long time);
        
        bool isKeyPressExecuteAction(int key);

        inline bool isPaused(){ return !running; }
        inline void pause(){ refreshStatuses_(); running = false; }

        std::list<Sprite *>::const_iterator firstNPC(){ return NPC_sprites.begin(); }
        std::list<Sprite *>::const_iterator lastNPC(){ return NPC_sprites.end(); }

        bool spawnNPC(int sprite_index, int distanceToGoal = DISTANCE_TO_PLAYER, int xpos = -1, int ypos = -1, float xface = 0, float yface = 0);

        int getNumFireballs(){ return numFireballs; }
        int getNumBombs(){ return numBombs; }
        int getMaxBombsAllow(){ return maxBombsAllow; }
        void updateNumBombs(int num){ numBombs += num; }
        void updateNumFireballs(int num){ numFireballs += num; }

        void removeNPC(Sprite* spr){ delete spr; NPC_sprites.remove(spr); }

    protected:
        void setMapTile_(int wall);
        void draw_(int** const generatedMap);



        int** const generatedMap_(void);

        inline void addNPC_(Sprite *spr){ NPC_sprites.push_back(spr); }

    private:
        int width;
        int height;

        bool running;

        int maxBombsAllow, numBombs;
        int numFireballs;

        unsigned long startTime;
        unsigned long elapsedTime;

        std::list <Sprite *> NPC_sprites;
        std::list <Sprite *>::const_iterator sprite_Iter;
        
        int** digitalMap = NULL;
        
        // the first sprite that has isKeyPressExecuteAction method (the human control sprite index)
        Character *player;
        
        DrawEngine *drawArea;

        void refreshStatuses_(void);
    };
}
#endif /* level_h */
