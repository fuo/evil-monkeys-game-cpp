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
    enum COLOR_CODE
    {
        WHITE_BLACK,
        RED_BLACK,
        WHITE_WHITE,
    };

    // friend class
    class Sprite;
    class Level;

    class DrawEngine
    {
    public:
        DrawEngine();
        ~DrawEngine();
        
        // manage the drawing material
        void createBackgroundTile(int tileIndex, char img);
        
        
        int registerSprite(int figureIndex, int img, int color = 0);

        // helpers
        void refresh(void){
            wrefresh(field);
            wrefresh(score);
        }
        void printScore(const char* text, int xpos, int ypos = 1){
            mvwprintw(score, ypos, xpos, text);
        }
        
        // manipulate the Level
        void setMap(int** grid, int xSize, int ySize);
        
        int getSpriteColor(int sprite_index){ return spriteColor[sprite_index]; }

        // make friend with Sprite so he can use those protected methods
        friend class Sprite;
        friend class Level;

    protected:
        // API for Sprite class only
        bool eraseSprite_(int xpos, int ypos);
        bool drawSprite_(int figureIndex, int xpos, int ypos, int color = 0);

        // API for Level class only
        void drawBackground_(void);

    private:
        WINDOW *field;
        WINDOW *score;
        
        // digitalize map of characters
        int** map = NULL;
        
        int screenWidth, screenHeight, score_size;
        
        char spriteImages[16];
        int spriteColor[16];
        
        char tileImages[16];
        
        // inner methods
        bool gotoxy_(int xpos, int ypos);
        int cursorVisibility_(int visibility){ return curs_set(visibility); }
        void draw_borders_(WINDOW*);
        
        void initNcurse_(void);
        void initColor_(void);
    };
}
#endif /* drawEngine_h */
