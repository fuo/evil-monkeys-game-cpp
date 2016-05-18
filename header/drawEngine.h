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
    };
    
    class DrawEngine
    {
    public:
        DrawEngine();
        ~DrawEngine();
        
        // manage the drawing material
        int createSprite(int figureIndex, int img, int color = 0);
        void createBackgroundTile(int tileIndex, char img);
        
        
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
        void drawBackground(void);
        
        // API
        bool eraseSprite(int xpos, int ypos);
        bool drawSprite(int figureIndex, int xpos, int ypos, int color = 0);
        
        int getSpriteColor(int sprite_index){ return spriteColor[sprite_index]; }

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
        bool gotoxy(int xpos, int ypos);
        int cursorVisibility(int visibility){ return curs_set(visibility); }
        void draw_borders(WINDOW*);
        
        void initNcurse(void);
        void initColor(void);
    };
}
#endif /* drawEngine_h */
