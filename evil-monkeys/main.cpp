//
//  main.cpp
//  evil-monkeys
//
//  Created by phuong on 5/9/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include <iostream>
#include <ncurses.h>

#include "game.hpp"

bool isTermAvail = false; // check this global variable before ncurses calls

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

    if (isTermAvail)
        isTermAvail = (initscr() != NULL);

//=========================================================
    
    Game game;

    game.run();
    
    
    if (isTermAvail)
    {
        printw("Press any key to exit...");
        refresh();

        getch();
        
        endwin();
    }

    return 0;
}
