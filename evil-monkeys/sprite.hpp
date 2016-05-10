//
//  sprite.hpp
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef sprite_hpp
#define sprite_hpp

#include "drawEngine.hpp"

enum
{
    SPRITE_CLASSID,
};

struct vector
{
    float x;
    float y;
};

class Sprite
{
public:
    Sprite(DrawEngine* de, int s_index, float xpos = 1, float ypos = 1, int i_lives = 1);
    ~Sprite();
    
    vector getPosition(void){ return pos; }
    float getX(void){ return pos.x; }
    float getY(void){ return pos.y; }
    
    virtual void addLives(int num = 1){ numLives += num; } // allow late-binding call using the same base pointer, if derived class has the same method, otherwise still use the inherit one from base
    int getLives(void){ return numLives; }
    bool isAlive(void){ return (numLives > 0); }
    
    virtual bool move(float xDir, float yDir);
    
    
    
protected:
    DrawEngine *drawArea;
    vector pos;
    int spriteIndex;
    int numLives;
    
private:
    int classID;
    
    vector facingDirection;
    
    void draw(float xpos, float ypos){ drawArea->drawSprite(spriteIndex, xpos, ypos); }
    void erase(float xpos, float ypos){ drawArea->eraseSprite(xpos, ypos); }
};

#endif /* sprite_hpp */
