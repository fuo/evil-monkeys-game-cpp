//
//  drawEngine.cpp
//  evil-monkeys
//
//  Created by phuong on 5/10/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "drawEngine.hpp"

#include <ncurses.h>

DrawEngine::DrawEngine(int screenW, int screenH)
{
    screenWidth = screenW;
    screenHeight = screenH;
    cursorVisibility(false);
}

DrawEngine::~DrawEngine()
{
    cursorVisibility(true);
}

int DrawEngine::createSprite(int figureIndex, char img)
{
    if (figureIndex >= 0 && figureIndex < 16) {
        spriteImages[figureIndex] = img;
        return figureIndex;
    }
    return -1;
}

bool DrawEngine::eraseSprite(int xpos, int ypos)
{
    gotoxy(xpos, ypos);
    addch(' ');
    refresh();
    
    return true;
}

bool DrawEngine::drawSprite(int figureIndex, int xpos, int ypos)
{
    gotoxy(xpos, ypos);
    addch(spriteImages[figureIndex]);
    refresh();
    
    return true;
}

bool DrawEngine::gotoxy(int xpos, int ypos)
{
    move(ypos, xpos);
    return true;
}

bool DrawEngine::cursorVisibility(bool visibility)
{
    curs_set(visibility);
    refresh();
    return true;
}