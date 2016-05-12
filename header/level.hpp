//
//  level.h
//  3dbuzz
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef level_h
#define level_h

#include <list>
using std::list;

#include "drawEngine.hpp"

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
    
    void addPlayer(Character *p){ player = p; }
    
    void update(void);
    
    bool keyPress(int key);
    
    void addEnemies(int num);
    
    void addNPC(Sprite *spr){ npc.push_back(spr); }
    
    void draw(void){ drawArea->drawBackground(); }
    
    list <Sprite *> npc;

    
    int numEnemies;
    
    char** const createLevel(void);
    
private:
    int width;
    int height;
    
    list <Sprite *>::iterator Iter;
    
    char **level = NULL;
    
    
    
    // the first sprite that has keypress method (the human control sprite index)
    Character *player;
    
    DrawEngine *drawArea;
};

#endif /* level_h */
