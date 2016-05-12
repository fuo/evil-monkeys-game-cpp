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
class DrawEngine;
class Character;
class Sprite;

class Level
{
public:
    Level(DrawEngine *de, int width = 30, int height = 20);
    ~Level();
    
    void addPlayer(Character *p);
    void update(void);
    void draw(void);
    bool keyPress(int c);
    
    void addEnemies(int num);
    void addNPC(Sprite *spr);
    
    list <Sprite *> npc;
    list <Sprite *>::iterator Iter;
    
    int numEnemies;
    
    char **level;
    
protected:
    void createLevel(void);
    
private:
    int width;
    int height;
    
    // the first sprite that has keypress method (the human control sprite index)
    Character *player;
    
    DrawEngine *drawArea;
};

#endif /* level_h */
