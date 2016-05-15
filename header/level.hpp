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

#include "drawEngine.hpp"

namespace EvilMonkeys
{
    enum
    {
        SPRITE_PLAYER,
        SPRITE_ENEMY,
        SPRITE_FIREBALL
    };

    enum
    {
        TILE_EMPTY,
        TILE_WALL
    };

    // notify ahead
    class Character;
    class Sprite;

    class Level
    {
    public:
        Level(DrawEngine *de, int width = 30, int height = 20);
        ~Level();
        
        inline int getWidth(){ return width; }
        inline int getHeight(){ return height; }
        
        inline int** getLevel(){ return level; }
        inline int checkGrid(int xpos, int ypos){ return level[xpos][ypos]; }
        
        inline void addPlayer(Character *p){ player = p; }
        
        void update(void);
        
        bool keyPress(int key);
        
        void addEnemies(int num);
        
        inline void addNPC(Sprite *spr){ npc.push_back(spr); }
        
        inline void draw(void){ drawArea->drawBackground(); }
        
        std::list <Sprite *> npc;

        
        int numEnemies;
        int numFireballs;
        
        int** const createLevel(void);
        
    private:
        int width;
        int height;
        
        std::list <Sprite *>::const_iterator Iter;
        
        int** level = NULL;
        
        
        
        // the first sprite that has keypress method (the human control sprite index)
        Character *player;
        
        DrawEngine *drawArea;
    };
}
#endif /* level_h */
