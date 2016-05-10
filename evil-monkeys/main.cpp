//
//  main.cpp
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include <iostream>
#include <ncurses.h>
using namespace std;
#include "game.hpp"

bool isTermAvail = true; // check this global variable before ncurses calls

typedef struct _win_border_struct {
    chtype 	ls, rs, ts, bs,
    tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {
    
    int startx, starty;
    int height, width;
    WIN_BORDER border;
}WIN;

void init_win_params(WIN *p_win);
void print_win_params(WIN *p_win);
void create_box(WIN *win, bool flag);

string leftPad(string, long, char padChar = ' ');
string rightPad(string, long, char padChar = ' ');


void draw_borders22(WINDOW *screen) {
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

int main55(int argc, const char * argv[]) {
    
    
    Game game;
    game.run();
    
//    endwin();
    
    return 0;
}

//int main333(int argc, const char * argv[]) {
//    int parent_x, parent_y, new_x, new_y;
//    int score_size = 3; // ...
//    draw_borders(field);
//    draw_borders(score);
//    while(1) { getmaxyx(stdscr, new_y, new_x);
//        if (new_y != parent_y || new_x != parent_x)
//        {
//            parent_x = new_x;
//            parent_y = new_y;
//            wresize(field, new_y - score_size, new_x);
//            wresize(score, score_size, new_x);
//            mvwin(score, new_y - score_size, 0);
//            wclear(stdscr);
//            wclear(field);
//            wclear(score);
//            draw_borders(field);
//            draw_borders(score); } // draw to our windows
//        mvwprintw(field, 1, 1, "Field");
//        mvwprintw(score, 1, 1, "Score"); // refresh each window
//        wrefresh(field); wrefresh(score);
//    } // ...
//}

int main(int argc, const char * argv[]) {
    
    for (int argi = 1; argi < argc; argi++)
    {
        if (isTermAvail && strcmp(argv[argi], "--debug-in-terminal") == 0)
        {
            printf("Debugging in terminal enabled\n");
            getchar(); // Without this call debugging will be skipped
            break;
        }
    }

    char *term = getenv("TERM");

    isTermAvail = (term != NULL);
    
    if (isTermAvail){
        isTermAvail = (initscr() != NULL);
        cbreak();			/* Line buffering disabled, Pass on
                             * everty thing to me 		*/
        keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
        noecho();
        scrollok(stdscr, TRUE);
        
    }

//=========================================================
    
    
    
    
//    cout << leftPad("ffasp", 14, '-') << "e" << endl;    
//    cout << rightPad("hello", 9, 'x') << endl;
    
//    WIN win;
//    int ch;
//    
////    initscr();			/* Start curses mode 		*/
//    curs_set(0);
//
//    start_color();			/* Start the color functionality */
//    cbreak();			/* Line buffering disabled, Pass on
//                         * everty thing to me 		*/
//    keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
//    noecho();
//    scrollok(stdscr, TRUE);
//    nodelay(stdscr, TRUE);
//    init_pair(1, COLOR_CYAN, COLOR_BLACK);
//    
//    /* Initialize the window parameters */
//    init_win_params(&win);
//    print_win_params(&win);
//    
//    attron(COLOR_PAIR(1));
//    printw("Press F1 to exit");
//    refresh();
//    attroff(COLOR_PAIR(1));
//    
//    create_box(&win, TRUE);
//    while((ch = getch()) != KEY_F(1))
//    {	switch(ch)
//        {	case KEY_LEFT:
//                create_box(&win, FALSE);
//                --win.startx;
//                create_box(&win, TRUE);
//                break;
//            case KEY_RIGHT:
//                create_box(&win, FALSE);
//                ++win.startx;
//                create_box(&win, TRUE);
//                break;
//            case KEY_UP:
//                create_box(&win, FALSE);
//                --win.starty;
//                create_box(&win, TRUE);
//                break;
//            case KEY_DOWN:
//                create_box(&win, FALSE);
//                ++win.starty;
//                create_box(&win, TRUE);
//                break;	
//        }
//    }
//    move(4,5);
//    addch('*');
//    mvprintw(5, 5, "xfasd");
    
    
    
    Game game;
    game.run();

    
    
    if (isTermAvail)
    {
        nodelay(stdscr, FALSE);
        
        printw("\n\n Press any key to exit... \n\n");
        refresh();

        getch();
        
        endwin();
    }

    return 0;
}

string leftPad(string str, long len, char padChar)
{
    long strlen = str.length(), i = -1, newlen = len;
    
    if (len < strlen)
        return str;
    
    char* const leftPaddedStr = new char[len];
    
    len -= strlen;
    
    while (++i < newlen) {
        if (i < len)
            leftPaddedStr[i] = padChar;
        else
            leftPaddedStr[i] = str[i - len];
    }
    leftPaddedStr[i] = '\0';
    
    str = leftPaddedStr;
    delete [] leftPaddedStr;
    
    return str;
}

// leftpad("hello", 8, *); => "***hello"

string rightPad(string str, long len, char padChar)
{
    long strlen = str.length(), i = -1, newlen = len;
    
    if (len < strlen)
        return str;
    
    char* const rightPaddedStr = new char[len];
    
    len -= strlen;
    
    while (++i < newlen) {
        if (i < strlen)
            rightPaddedStr[i] = str[i];
        else
            rightPaddedStr[i] = padChar;
    }
    rightPaddedStr[i] = '\0';
    
    str = rightPaddedStr;
    delete [] rightPaddedStr;
    
    return str;
}


void init_win_params(WIN *p_win)
{
    p_win->height = 3;
    p_win->width = 10;
    p_win->starty = (LINES - p_win->height)/2;
    p_win->startx = (COLS - p_win->width)/2;
    
    p_win->border.ls = '|';
    p_win->border.rs = '|';
    p_win->border.ts = '-';
    p_win->border.bs = '-';
    p_win->border.tl = '+';
    p_win->border.tr = '+';
    p_win->border.bl = '+';
    p_win->border.br = '+';
    
}
void print_win_params(WIN *p_win)
{
#ifdef _DEBUG
    mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty,
             p_win->width, p_win->height);
    refresh();
#endif
}
void create_box(WIN *p_win, bool flag)
{	int i, j;
    int x, y, w, h;
    
    x = p_win->startx;
    y = p_win->starty;
    w = p_win->width;
    h = p_win->height;
    
    if(flag == TRUE)
    {	mvaddch(y, x, p_win->border.tl);
        mvaddch(y, x + w, p_win->border.tr);
        mvaddch(y + h, x, p_win->border.bl);
        mvaddch(y + h, x + w, p_win->border.br);
        mvhline(y, x + 1, p_win->border.ts, w - 1);
        mvhline(y + h, x + 1, p_win->border.bs, w - 1);
        mvvline(y + 1, x, p_win->border.ls, h - 1);
        mvvline(y + 1, x + w, p_win->border.rs, h - 1);
        
    }
    else
        for(j = y; j <= y + h; ++j)
            for(i = x; i <= x + w; ++i)
                mvaddch(j, i, ' ');
				
    refresh();
    
}