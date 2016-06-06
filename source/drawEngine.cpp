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

    for (int i = 0; i < 16; i++)
    {
        spriteColor_[i] = -1;
        spriteImages_[i] = -1;
    }
}

DrawEngine::~DrawEngine()
{
    cursorVisibility_(true);
    endwin();
    delwin(field_);
    delwin(score_);
}

void DrawEngine::initColor_()
{
    start_color();			/* Start color 			*/
    init_pair(WHITE_WHITE, COLOR_WHITE, COLOR_WHITE);
    init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
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

    score_size_ = 3; // the height of score window

    // set up initial windows
    getmaxyx(stdscr, parent_y, parent_x);

    // initialize screen size by default terminal windows
    screenWidth_ = parent_x;
    screenHeight_ = parent_y - score_size_;

    field_ = newwin(screenHeight_, screenWidth_, 0, 0);
    score_ = newwin(score_size_, screenWidth_, screenHeight_, 0);

    draw_borders_(score_);

    // re-sizing
    getmaxyx(stdscr, new_y, new_x);

    if (new_y != parent_y || new_x != parent_x) {
        parent_x = new_x;
        parent_y = new_y;

        wresize(field_, new_y - score_size_, new_x);
        wresize(score_, score_size_, new_x);
        mvwin(score_, new_y - score_size_, 0);

        wclear(stdscr);
        wclear(field_);
        wclear(score_);

        draw_borders_(field_);
        draw_borders_(score_);
    }
}

void DrawEngine::setMap_(int** grid, int xSize, int ySize)
{
    map_ = grid;

    screenWidth_ = xSize;
    screenHeight_ = ySize;

    field_ = newwin(screenHeight_, screenWidth_, 0, 0);
    score_ = newwin(score_size_, screenWidth_, screenHeight_, 0);

    draw_borders_(score_);
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
    if (img == -1 && spriteImages_[figureIndex] != -1)
        return figureIndex;

    if (figureIndex >= 0 && figureIndex < 16)
    {
        spriteImages_[figureIndex] = img;

        if ( spriteColor_[figureIndex] < 0 || color > 0 )
            spriteColor_[figureIndex] = color;

        return figureIndex;
    }

    return -1;
}

bool DrawEngine::eraseSprite_(int xpos, int ypos)
{
    if(!gotoxy_(xpos, ypos))
        return false;

    return !waddch(field_, ' ');
}

bool DrawEngine::drawSprite_(int figureIndex, int xpos, int ypos, int color)
{
    if( !gotoxy_(xpos, ypos) )
        return false;

    if (color)
        return !waddch(field_, spriteImages_[figureIndex] | COLOR_PAIR(color) );

    return !waddch(field_, spriteImages_[figureIndex] | COLOR_PAIR(spriteColor_[figureIndex]) );
}

bool DrawEngine::gotoxy_(int xpos, int ypos)
{
    if ( xpos > screenWidth_ || xpos < 0 || ypos > screenHeight_ || ypos < 0 )
        return false;

    return !wmove(field_, ++ypos, ++xpos);
}

// to the Level
void DrawEngine::createBackgroundTile_(int tileIndex, char img)
{
    if (tileIndex >= 0 && tileIndex < 16)
        tileImages_[tileIndex] = img;
}

void DrawEngine::drawBackground_()
{
    if (map_)
        for (int y = 0; y < screenHeight_; y++)
        {
            gotoxy_(0, y);

            for (int x = 0; x < screenWidth_; x++)
                if (tileImages_[map_[x][y]] != ' ')
                    waddch(field_, tileImages_[map_[x][y]] | COLOR_PAIR(WHITE_WHITE));
                else
                    waddch(field_, tileImages_[map_[x][y]]);
        }
}