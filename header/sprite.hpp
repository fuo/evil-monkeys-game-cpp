//
//  sprite.h
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef sprite_h
#define sprite_h

#include "drawEngine.hpp"

namespace EvilMonkeys
{
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

    class Level;

    class Sprite
    {
    public:
        Sprite(Level* l, DrawEngine* de, int sprite_index, float xpos = 1, float ypos= 1, int i_lives = 1);
        
        ~Sprite()
        {
            // erase the dying sprites
            erase(pos.x, pos.y);
        }
        
        vector getPosition(void){ return pos; }
        float getX(void){ return pos.x; }
        float getY(void){ return pos.y; }
        void setPosition(float x, float y) { pos.x = x; pos.y = y; }
        
        int getLives(void){ return numLives; }
        
        virtual void addLives(int num = 1){ numLives += num; }
        
        virtual void idleUpdate(void)
        {
            // this is only for the inhereited classes not for myself
        }
        virtual bool move(float xDir, float yDir);
        
        int getClassID(void){ return classID; }
        void setClassID(int id){ classID = id; }
        
    protected:
        vector facingDirection;
        
        DrawEngine* drawArea;
        
        void draw(float x, float y)
        {
            drawArea->drawSprite(spriteIndex, (int)x, (int)y);
        }
        
        void erase(float x, float y)
        {
            drawArea->eraseSprite((int)x, (int)y);
        }
        
        Level* level;
        // aware of level map
        bool isValidLevelMove(int xpos, int ypos);
        
    private:
        int classID, spriteIndex, numLives;
        vector pos;
    };
}
#endif /* sprite_h */
