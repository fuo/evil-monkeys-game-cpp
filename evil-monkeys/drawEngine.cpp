//
//  drawEngine.cpp
//  evil-monkeys
//
//  Created by phuong on 5/10/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "drawEngine.hpp"

DrawEngine::DrawEngine(int screenW, int screenH)
{
    initscr();
    
    cbreak();			/* Line buffering disabled, Pass on
                         * everty thing to me 		*/
    keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
    noecho();
    scrollok(stdscr, TRUE);

    
    int parent_x, parent_y, new_x, new_y;
    
    int score_size = 3; // the height of score window
    
    // set up initial windows
    getmaxyx(stdscr, parent_y, parent_x);
    
    field = newwin(parent_y - score_size, parent_x, 0, 0);
    score = newwin(score_size, parent_x, parent_y - score_size, 0);
    
    draw_borders(field);
    draw_borders(score);
    
    
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
        
        draw_borders(field);
        draw_borders(score);
    }
    
//    // draw to our windows
//    mvwprintw(field, 1, 1, "Field");
//    mvwprintw(score, 1, 1, "Score");
//    
//    // refresh each window
//    wrefresh(field);
//    wrefresh(score);
    
    
    screenWidth = screenW;
    screenHeight = screenH;
    
    cursorVisibility(false);
}

DrawEngine::~DrawEngine()
{
    cursorVisibility(true);
    endwin();
    delwin(field);
    delwin(score);
}

void DrawEngine::setup()
{
    
    // draw to our windows
    mvwprintw(field, 1, 1, "Field");
    mvwprintw(score, 1, 1, "Score");
    
    // refresh each window
    wrefresh(field);
    wrefresh(score);
    
}

void DrawEngine::draw_borders(WINDOW *screen) {
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
    waddch(field, ' ');
//    refresh();
    
    return true;
}

bool DrawEngine::drawSprite(int figureIndex, int xpos, int ypos)
{
    gotoxy(xpos, ypos);
    waddch(field, spriteImages[figureIndex]);
//    wrefresh(score);
    
    return true;
}

bool DrawEngine::gotoxy(int xpos, int ypos)
{
    wmove(field, ++ypos, ++xpos);
//    wrefresh(score);
    return true;
}

bool DrawEngine::cursorVisibility(bool visibility)
{
    curs_set(visibility);
    refresh();
    return true;
}