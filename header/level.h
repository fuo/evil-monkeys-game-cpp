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

namespace EvilMonkeys
{
    enum
    {
        SPRITE_PLAYER,
        SPRITE_ENEMY,
        SPRITE_FIREBALL,
        SPRITE_BOMB,
    };

    enum
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

        bool checkMapTileEmpty(int xpos, int ypos);
        
        inline void addPlayer(Character *p){ player = p; }
        
        void update(unsigned long time);
        
        bool isKeyPressExecuteAction(int key);

        inline bool isPaused(){ return !running; }
        std::list<Sprite *>::const_iterator firstNPC(){ return NPC_sprites.begin(); }
        std::list<Sprite *>::const_iterator lastNPC(){ return NPC_sprites.end(); }

        void spawnNPC(int num, int sprite_index);

    protected:
        void setMapTile_(int wall);
        void draw_(int** const generatedMap);

        void spawnEnemies_(int num, int enemySprite);

        int** const generatedMap_(void);

        inline void addNPC_(Sprite *spr){ NPC_sprites.push_back(spr); }

    private:
        int width;
        int height;

        bool running;

        int numEnemies;

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
