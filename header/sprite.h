//
//  sprite.h
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef sprite_h
#define sprite_h

#include "drawEngine.h"

namespace EvilMonkeys
{
    enum
    {
        SPRITE_CLASSID,
        CHARACTER_CLASSID,
        ENEMY_CLASSID,
        FIREBALL_CLASSID,
        MAGE_CLASSID,
        BOMB_CLASSID,
    };

    struct vector
    {
        float x;
        float y;
    };

    class Sprite
    {
    public:
        Sprite(DrawEngine* de, int sprite_index, float xpos = 1, float ypos= 1, int i_lives = 1);
        
        ~Sprite(){
            // erase the dying sprites
            erase(pos.x, pos.y);
        }
        
        inline vector getPosition(void){ return pos; }
        inline float getX(void){ return pos.x; }
        inline float getY(void){ return pos.y; }
        inline void setPosition(float x, float y) { pos.x = x; pos.y = y; }
        inline void setFacingDirection(float x, float y) { facingDirection.x = x; facingDirection.y = y; }
        
        inline int getLives(void){ return numLives; }
        
        virtual void __addLives(int num = 1){
            numLives += num;
        }
        
        inline virtual void __idleUpdate(void)
        {
            // this is only for the inhereited classes not for myself
            // because it's too early to know what should be implemented here
            // but I can use it as the interface for all of my children
            // thanks virtual late-binding... apply based pointer!
        }
        virtual bool __move(float xDir, float yDir);
        
        inline int getClassID(void){ return classID; }
        inline void setClassID(int id){ classID = id; }
        
    protected:
        vector facingDirection;
        
        DrawEngine* drawArea;
        
        void draw(float x, float y, int color = 0);

        inline void erase(float x, float y){
            drawArea->eraseSprite((int)x, (int)y);
        }


    private:
        int classID, spriteIndex, numLives;
        vector pos;
    };
}
#endif /* sprite_h */
