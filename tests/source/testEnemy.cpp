//
//  testEnemy.cpp
//  evil-monkeys
//
//  Created by phuong on 5/14/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "enemy.hpp"

#include "level.hpp"
using namespace EvilMonkeys;

#include "catch.hpp"


SCENARIO("--Enemy is forced to have ONE live only--", "[enemy]")
{
    DrawEngine de;
    Level lvl(&de);
    std::list<Sprite*>::iterator enemy;
    
    def_prog_mode();
    endwin();
    
    GIVEN("An enemy is spawn in the level")
    {
        
        lvl.addEnemies(1);
        enemy = lvl.npc.begin();

        
        REQUIRE(lvl.npc.size() == 1);
        
        WHEN("deduce its live by 1")
        {
            (*enemy)->__addLives(-1);
            
            AND_WHEN("fasfa fas fas ")
            {
                THEN("it should be dead")
                {
                    REQUIRE( (*enemy)->getLives() == 1 );
                }
            }
        }
        
    }
    
    GIVEN("--fdsafsaff  fsafas--")
    {
        
    }
    
    reset_prog_mode();
    refresh();
}
