//
//  sprite.h
//  3dbuzz
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef sprite_h
#define sprite_h

#include "drawEngine.hpp"
#include "level.hpp"

enum
{
    SPRITE_CLASSID,
    CHARACTER_CLASSID,
    ENEMY_CLASSID,
    FIREBALL_CLASSID,
    MAGE_CLASSID
};

struct vector
{
    float x;
    float y;
};

class Sprite
{
public:
    Sprite(Level *l, DrawEngine *de, int s_index, float x = 1, float y= 1, int i_lives =1);
    ~Sprite();
    
    vector getPosition(void);
    float getX(void);
    float getY(void);
    
    virtual void addLives(int num = 1);
    int getLives(void);
    bool isAlive(void);
    
    virtual void idleUpdate(void);
    
    virtual bool move(float x, float y);
    
    int classID;
    
protected:
    Level *level;
    DrawEngine *drawArea;
    int spriteIndex;
    vector pos;
    int numLives;
    
    
    vector facingDirection;
    
    void draw(float x, float y);
    void erase(float x, float y);
    
    bool isValidLevelMove(int xpos, int ypos);
    
};

#endif /* sprite_h */
