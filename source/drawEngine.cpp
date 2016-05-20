//
//  drawEngine.cpp
//  evil-monkeys
//
//  Created by phuong on 5/10/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "drawEngine.h"

using namespace EvilMonkeys;

DrawEngine::DrawEngine()
{
    initNcurse_();
    
    cursorVisibility_(false);

    for (int i = 0; i < 16; i++) {
        spriteColor[i] = -1;
    }
    
}

DrawEngine::~DrawEngine()
{
//    attroff(COLOR_PAIR(RED_WHITE));
    
    cursorVisibility_(true);
    endwin();
    delwin(field);
    delwin(score);
}

void DrawEngine::initColor_()
{
    start_color();			/* Start color 			*/
    init_pair(WHITE_WHITE, COLOR_WHITE, COLOR_WHITE);
    init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
}

void DrawEngine::initNcurse_()
{
    /* Initialize curses mode */
    initscr();
    
    if(has_colors() == FALSE)
    {	endwin();
        printf("Your terminal does not support color\n");
//        exit(1);
    }
    
    initColor_();

    //    attron(COLOR_PAIR(RED_WHITE));
    
    clear();
    cbreak();			/* Line buffering disabled, Pass on
                         * everty thing to me 		*/
    keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
    noecho();
    scrollok(stdscr, TRUE);
    
    int parent_x, parent_y, new_x, new_y;
    
    score_size = 3; // the height of score window
    
    // set up initial windows
    getmaxyx(stdscr, parent_y, parent_x);
    
    // initialize screen size by default terminal windows
    screenWidth = parent_x;
    screenHeight = parent_y - score_size;
    
    field = newwin(screenHeight, screenWidth, 0, 0);
    score = newwin(score_size, screenWidth, screenHeight, 0);
    
    draw_borders_(score);
    
    // re-sizing
    getmaxyx(stdscr, new_y, new_x);
    
    if (new_y != parent_y || new_x != parent_x) {
        parent_x = new_x;
        parent_y = new_y;
        
        wresize(field, new_y - score_size, new_x);
        wresize(score, score_size, new_x);
        mvwin(score, new_y - score_size, 0);
        
        wclear(stdscr);
        wclear(field);
        wclear(score);
        
        draw_borders_(field);
        draw_borders_(score);
    }
}

void DrawEngine::setMap(int** grid, int xSize, int ySize)
{
    map = grid;
    
    screenWidth = xSize;
    screenHeight = ySize;
    
    field = newwin(screenHeight, screenWidth, 0, 0);
    score = newwin(score_size, screenWidth, screenHeight, 0);
    
    draw_borders_(score);
}

void DrawEngine::draw_borders_(WINDOW *screen) {
    int x, y, i;
    
    getmaxyx(screen, y, x);
    
    // 4 corners
    mvwprintw(screen, 0, 0, "+");
    mvwprintw(screen, y - 1, 0, "+");
    mvwprintw(screen, 0, x - 1, "+");
    mvwprintw(screen, y - 1, x - 1, "+");
    
    // sides
    for (i = 1; i < (y - 1); i++) {
        mvwprintw(screen, i, 0, "|");
        mvwprintw(screen, i, x - 1, "|");
    }
    
    // top and bottom
    for (i = 1; i < (x - 1); i++) {
        mvwprintw(screen, 0, i, "-");
        mvwprintw(screen, y - 1, i, "-");
    }
}

int DrawEngine::registerSprite(int figureIndex, int img, int color)
{
    if (figureIndex >= 0 && figureIndex < 16)
    {
        spriteImages[figureIndex] = img;

        if ( spriteColor[figureIndex] < 0 || color > 0 )
            spriteColor[figureIndex] = color;

        return figureIndex;
    }
    return -1;
}

bool DrawEngine::eraseSprite_(int xpos, int ypos)
{
    if(!gotoxy_(xpos, ypos))
        return false;
    
    waddch(field, ' ');
    return true;
}

bool DrawEngine::drawSprite_(int figureIndex, int xpos, int ypos, int color)
{
    if( !gotoxy_(xpos, ypos) )
        return false;
    
    if (color)
    {
        waddch(field, spriteImages[figureIndex] | COLOR_PAIR(color) );
        return true;
    }
    
    waddch(field, spriteImages[figureIndex] | COLOR_PAIR(spriteColor[figureIndex]) );
    
    return true;
}

bool DrawEngine::gotoxy_(int xpos, int ypos)
{
    if ( xpos > screenWidth || xpos < 0 || ypos > screenHeight || ypos < 0 )
        return false;
    
    wmove(field, ++ypos, ++xpos);
    return true;
}

// to the Level
void DrawEngine::createBackgroundTile(int tileIndex, char img)
{
    if (tileIndex >= 0 && tileIndex < 16)
    {
        tileImages[tileIndex] = img;
    }
}

void DrawEngine::drawBackground_()
{
    if (map)
    {
        for (int y = 0; y < screenHeight; y++)
        {
            gotoxy_(0, y);
            
            for (int x = 0; x < screenWidth; x++)
            {
                if (tileImages[map[x][y]] != ' ') {
                    waddch(field, tileImages[map[x][y]] | COLOR_PAIR(WHITE_WHITE));
                } else {
                    waddch(field, tileImages[map[x][y]]);
                }

            }
            
        }
        
    }
    
}

