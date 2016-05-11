//
//  level.hpp
//  evil-monkeys
//
//  Created by phuong on 5/11/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef level_hpp
#define level_hpp

#include <list>
using std::list;

class DrawEngine;
class Sprite;
class Character;

enum
{
    SPRITE_PLAYER,
    SPRITE_ENEMY,
};

enum
{
    TILE_EMPTY,
    TILE_WALL
};

class Level
{
public:
    Level(DrawEngine *de, int width = 20, int height = 20);
    ~Level();
    
    bool addPlayer(Character *p, int xpos = 0, int ypos = 0);
    void update(void);
    void draw(void);
    bool keyPress(int key);
    
    bool addEnemies(int num);
    void addNPC(Sprite *spr);
    
    friend class Sprite;
    
    list <Sprite *> npc;
    list <Sprite *>::iterator Iter;
    
    char** level;
    
protected:
    
    

    void create(void);
    
private:

    Character *player;
    DrawEngine *drawArea;
    
    
    
    int width, height;
};

#endif /* level_hpp */
