//
//  testEnemy.cpp
//  evil-monkeys
//
//  Created by phuong on 5/14/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "enemy.hpp"

#include <iostream>
#include <ncurses.h>
using namespace std;

#include "level.hpp"
#include "mage.hpp"
#include "fireball.hpp"
using namespace EvilMonkeys;

#include "catch.hpp"


SCENARIO("--Enemy will hunt down a character--", "[enemy]")
{
//    getchar();
    
    DrawEngine de;
    Level* lvl = new Level(&de);
    
    def_prog_mode();
    endwin();
    
    GIVEN("An enemy is spawn in the level")
    {
        Enemy* evilMonkey = NULL;
        int xpos = 0, ypos = 0;
        
        do{
//            srand((unsigned int)time(0));
            xpos = int((float(rand() % 100) / 100) * (lvl->getWidth() - 2) + 1);
            srand(xpos);
            ypos = int((float(rand() % 100) / 100) * (lvl->getHeight() - 2) + 1);
        
        }while (lvl->checkGrid(xpos, ypos) == TILE_WALL);
        
        REQUIRE(lvl->checkGrid(xpos, ypos) != TILE_WALL);
        
        evilMonkey = new Enemy(lvl, &de, SPRITE_ENEMY, (float)xpos, float(ypos));
        
        REQUIRE(evilMonkey->getLives() == 1);
        
        CHECK(lvl->npc.size() == 0);
        
        WHEN("it sees a target")
        {
            Character* player = new Character(lvl, &de, SPRITE_PLAYER);
            
            evilMonkey->addGoal(player);
            
            REQUIRE(player->getLives() >= 1);
            
            AND_WHEN("it is chasing the goal")
            {
                Sprite* sprite_enemy = evilMonkey;
                
                float oldx = evilMonkey->getX();
                float oldy = evilMonkey->getY();
                
                sprite_enemy->__idleUpdate();
                
                REQUIRE(oldx != evilMonkey->getX());
                REQUIRE(oldy != evilMonkey->getY());
                
                AND_WHEN("a) it hits the target")
                {
                    player->setPosition(evilMonkey->getX(), evilMonkey->getY());
                    
                    REQUIRE(player->getX() == evilMonkey->getX());
                    REQUIRE(player->getY() == evilMonkey->getY());
                    
                    THEN("it kills the player")
                    {
                        sprite_enemy->__idleUpdate();
                        REQUIRE(player->getLives() == 2);
                        REQUIRE(evilMonkey->getLives() == 1);
                        
                        AND_THEN("reset the position of the player if still alive")
                        {
                            REQUIRE(player->getX() == 1);
                            REQUIRE(player->getY() == 1);
                        }
                    }
                }
                
                AND_WHEN("b) the player can cast spell")
                {
                    delete player;
                    
                    player = new Mage(lvl, &de, SPRITE_PLAYER);
                    
                    player->__isKeyPressExecuteAction(' ');
                    
                    REQUIRE(lvl->numFireballs > 0);
                    
                    AND_WHEN("i) it got hit by the fireball")
                    {
                        lvl->addNPC(sprite_enemy);
                        
                        Fireball* ball = new Fireball(lvl, &de, SPRITE_FIREBALL, evilMonkey->getX(), evilMonkey->getY(), 0, 0);
                        
                        sprite_enemy = ball;
                        
                        THEN("it should be dead")
                        {
                            sprite_enemy->__idleUpdate();
                            
                            REQUIRE( evilMonkey->getLives() == 0 );
                            
                            AND_THEN("the fireball should also be dead")
                            {
                                REQUIRE(ball->getLives() == 0);
                            }
                        }
                        
                        delete ball;
                        
                    }
                    AND_WHEN("ii) the fireball hits the wall")
                    {
                        typename std::list<Sprite *>::const_iterator Iter = lvl->npc.begin();
                        typename std::list<Sprite *>::const_iterator itEnd = lvl->npc.end();
                        
                        Fireball* theBall = nullptr;
                        
                        for( ; Iter != itEnd; ++Iter )
                        {
                            if ((*Iter)->getClassID() == FIREBALL_CLASSID && lvl->numFireballs == 1) {
                                theBall = (Fireball*)(*Iter);
                                break;
                            }
                        }
                        
                        do{
                            srand((unsigned int)time(0));
                            xpos = int((float(rand() % 100) / 100) * (lvl->getWidth() - 2) + 1);
                            srand(xpos + (unsigned int)time(0));
                            ypos = int((float(rand() % 100) / 100) * (lvl->getHeight() - 2) + 1);
                            
                        }while (lvl->checkGrid(xpos, ypos) == TILE_EMPTY);
                        
                        theBall->setPosition(xpos, ypos);
                        theBall->setFacingDirection(0, 0);
                        
                        delete sprite_enemy;
                        sprite_enemy = theBall;
                        
                        sprite_enemy->__idleUpdate();
                        
                        THEN("it should kill itself")
                        {
                            REQUIRE(theBall->getLives() == 0);
                            REQUIRE(lvl->numFireballs == 0);
                        }
                    }
                }
                
            }
            
        }
        
        
        
    }
    
    
    
    delete lvl;
    
    reset_prog_mode();
    refresh();
    
//    getch();
//    endwin();
//    CATCH_BREAK_INTO_DEBUGGER()
}
