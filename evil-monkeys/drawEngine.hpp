//
//  drawEngine.hpp
//  evil-monkeys
//
//  Created by phuong on 5/10/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef drawEngine_hpp
#define drawEngine_hpp

#include <ncurses.h>

class DrawEngine
{
public:
    DrawEngine();
    ~DrawEngine();
    
    int createSprite(int figureIndex, char img);
    bool deleteSprite(int figureIndex);
    
    bool eraseSprite(int xpos, int ypos);
    bool drawSprite(int figureIndex, int xpos, int ypos);
    
    void printScore(int xpos, int ypos, const char*);
    
    // to the Level
    void createBackgroundTile(int tileIndex, char img);
    void setMap(char** grid, int xSize, int ySize);
    void drawBackground(void);
    
    void setup(void);
    
protected:
    
    char** map;
    
    int screenWidth, screenHeight, score_size;
    
    char spriteImages[16];
    char tileImages[16];
    
private:
    bool gotoxy(int xpos, int ypos);
    bool cursorVisibility(bool visibility);
    void draw_borders(WINDOW*);
    
    WINDOW *field;
    WINDOW *score;
    
};

#endif /* drawEngine_hpp */
