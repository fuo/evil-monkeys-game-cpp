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
    struct vector
    {
        float x;
        float y;
    };

    class Level;

    class Sprite
    {
        int spriteIndex_;
        
    protected:
        vector pos_;
        vector facingDirection_;

        int numLives_, classID_;
        bool isNPC_;
        DrawEngine* drawArea_;
        Level* level_;

    public:
        Sprite(DrawEngine* de, int sprite_index, float xpos = 1, float ypos= 1, int i_lives = 1)
        : classID_{SPRITE_CLASSID}
        , drawArea_{de}
        , spriteIndex_{sprite_index}
        , numLives_{i_lives}
        , isNPC_{true}
        , pos_{xpos, ypos}
        , facingDirection_{1, 0}
        {

        }
        
        ~Sprite(){
            // erase the dying sprites
            erase_();

            // and re-draw the still alive sprite that happen to be on the same spot of the dying sprite (in case of pick up something)
        }
        
        inline vector getPosition(void){ return pos_; }
        inline float getX(void){ return pos_.x; }
        inline float getY(void){ return pos_.y; }
        inline void setPosition(float x, float y) { pos_.x = x; pos_.y = y; }
        inline void resetPosition(){ setPosition(1, 1); draw_(); }
        inline void setFacingDirection(float x, float y) { facingDirection_.x = x; facingDirection_.y = y; }
        inline float getFaceX(void){ return facingDirection_.x; }
        inline float getFaceY(void){ return facingDirection_.y; }

        inline void setSpriteIndex(int new_index){ spriteIndex_ = new_index; }
        bool matchCurrentLocation(int xpos, int ypos);
        bool matchCurrentFacingDir(vector dir = {0,0});

        inline int getLives(void){ return numLives_; }

        inline virtual void __addLives(int num = 1){ numLives_ += num; }

        inline auto const getLevel(){ return level_; }

        inline virtual void __idleUpdate(void)
        {
            // this is only for the inhereited classes not for myself
            // because it's too early to know what should be implemented here
            // but I can use it as the interface for all of my children
            // thanks virtual late-binding... apply based pointer!
        }
        virtual bool __move(float xDir, float yDir);
        
        inline int getClassID(void){ return classID_; }
        inline void setClassID(int id){ classID_ = id; }

        inline bool is(int id){ return classID_ == id; }

        inline void nonNPC(){ isNPC_ = false; }

        bool isValidLevelMove(int xpos, int ypos);

        bool hits(Sprite* other);

        virtual bool __hookToLevel(Level* lvl, bool draw_at_once = true);

        void draw_(float x = -1, float y = -1);

    protected:
        virtual void erase_(void);

    };
}
#endif /* sprite_h */
