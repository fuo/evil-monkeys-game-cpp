//
//  game.cpp
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//
#include "game.hpp"

#include <sys/time.h>
#include <ncurses.h>

#define GAME_SPEED 50

void draw_borders(WINDOW *screen);

int kbhit(void);
bool getKeyInput(char&);

void Game::run()
{
    double lastTime = 0;
    char key = ' ';
    
    nodelay(stdscr, TRUE);
    
    
    int parent_x, parent_y, new_x, new_y;
    int score_size = 3;
    
    initscr();
    noecho();
    curs_set(FALSE);
    
    // set up initial windows
    getmaxyx(stdscr, parent_y, parent_x);
    
    WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0);
    WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0);
    
    draw_borders(field);
    draw_borders(score);

    
    while (key != 'q') {
        
        
        
        while (!getKeyInput(key)) {
            
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
            
            // draw to our windows
            mvwprintw(field, 1, 1, "Field");
            mvwprintw(score, 1, 1, "Score");
            
            // refresh each window
            wrefresh(field);
            wrefresh(score);
            
            this->timerUpdate(lastTime);
        }
        // pass the pressed key to the level
    }

    
    
//    while(1) {
//        getmaxyx(stdscr, new_y, new_x);
//        
//        if (new_y != parent_y || new_x != parent_x) {
//            parent_x = new_x;
//            parent_y = new_y;
//            
//            wresize(field, new_y - score_size, new_x);
//            wresize(score, score_size, new_x);
//            mvwin(score, new_y - score_size, 0);
//            
//            wclear(stdscr);
//            wclear(field);
//            wclear(score);
//            
//            draw_borders(field);
//            draw_borders(score);
//        }
//        
//        // draw to our windows
//        mvwprintw(field, 1, 1, "Field");
//        mvwprintw(score, 1, 1, "Score");
//        
//        // refresh each window
//        wrefresh(field);
//        wrefresh(score);
//    }

    
//    int ch;
//    nodelay(stdscr, TRUE);
//    for (;;) {
//        if ((ch = getch()) == ERR) {
//            /* user hasn't responded
//             ...
//             */
//        }
//        else {
//            /* user has pressed a key ch
//             ...
//             */
//        }
//    }
    
}
int i = 0;
void Game::timerUpdate(double & lastTime)
{
    timeval* tv = new timeval();
    gettimeofday(tv, 0);
    
    double currentTime = (tv->tv_sec + double(tv->tv_usec)/1000000.0)*1000 - lastTime;
    
    if (currentTime < GAME_SPEED) {
        return;
    }
    
    // level update automatically
    
//    printw("fafa afas");
    
    drawArea.createSprite(0, '*');
    drawArea.drawSprite(0, ++i, 1);
    
    gettimeofday(tv, 0);
    lastTime = (tv->tv_sec + double(tv->tv_usec)/1000000.0)*1000;
}


bool getKeyInput(char & key)
{
    if (kbhit()) {
        key = getch();
        
        return true;
    }
    
    return false;
}

int kbhit()
{
    int ch = getch();
    
    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}


void draw_borders(WINDOW *screen) {
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