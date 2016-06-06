//
//  drawEngine.h
//  evil-monkeys
//
//  Created by phuong on 5/10/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef drawEngine_h
#define drawEngine_h

#include <ncurses.h>

namespace EvilMonkeys
{
    enum sprite_ID
    {
        SPRITE_PLAYER,
        SPRITE_ENEMY,
        SPRITE_FIREBALL,
        SPRITE_BOMB,
        SPRITE_ENEMY_1,
    };

    enum classID
    {
        SPRITE_CLASSID,
        CHARACTER_CLASSID,
        ENEMY_CLASSID,
        FIREBALL_CLASSID,
        MAGE_CLASSID,
        BOMB_CLASSID,
        EVILMONKEY_CLASSID,
    };

    enum COLOR_CODE
    {
        WHITE_BLACK,
        RED_BLACK,
        WHITE_WHITE,
        GREEN_BLACK,
        YELLOW_BLACK,
    };

    // friend class
    class Sprite;
    class Level;

    class DrawEngine
    {
        WINDOW *field_;
        WINDOW *score_;

        // digitalize map of characters
        int** map_;

        int screenWidth_, screenHeight_, score_size_;

        char spriteImages_[16];
        int spriteColor_[16];
        char tileImages_[16];

    public:
        // make friend with Sprite so he can use those protected methods
        friend class Sprite;
        friend class Level;

        DrawEngine();
        ~DrawEngine();
        
        // manage the drawing material
        int registerSprite(int figureIndex, int img = -1, int color = 0);

        // helpers
        void refresh(void){
            wrefresh(field_);
            wrefresh(score_);
        }
        void printScore(const char* text, int xpos, int ypos = 1){
            mvwprintw(score_, ypos, xpos, text);
        }
        
        int getSpriteColor(int sprite_index){ return spriteColor_[sprite_index]; }

    protected:
        // API for Sprite class only
        bool eraseSprite_(int xpos, int ypos);
        bool drawSprite_(int figureIndex, int xpos, int ypos, int color = 0);

        // API for Level class only
        void createBackgroundTile_(int tileIndex, char img);
        void drawBackground_(void);
        void setMap_(int** grid, int xSize, int ySize);

    private:
        // inner methods
        bool gotoxy_(int xpos, int ypos);
        int cursorVisibility_(int visibility){ return curs_set(visibility); }
        void draw_borders_(WINDOW*);
        
        void initNcurse_(void);
        void initColor_(void);
    };
}
#endif /* drawEngine_h */
