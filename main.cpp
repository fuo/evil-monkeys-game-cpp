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

string leftPad(string, long, char padChar = ' ');
string rightPad(string, long, char padChar = ' ');

int main(int argc, const char * argv[])
{
    for (int argi = 1; argi < argc; argi++)
    {
        if (isTermAvail && strcmp(argv[argi], "--debug-in-terminal") == 0)
        {
            printf("Debugging in terminal enabled\n");
            getchar(); // Without this call debugging will be skipped
            break;
        }
    }

    isTermAvail = (getenv("TERM") != NULL);
    
    
    EvilMonkeys::Game game;
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
    
    while (++i < newlen)
    {
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
    
    while (++i < newlen)
    {
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