//
//  testEnemy.cpp
//  evil-monkeys
//
//  Created by phuong on 5/14/16.
//  Copyright © 2016 badila. All rights reserved.
//

#include "enemy.h"

#include <iostream>
#include <ncurses.h>
using namespace std;

#include "level.h"
#include "mage.h"
#include "fireball.h"
using namespace EvilMonkeys;

#include "catch.hpp"


SCENARIO("--Enemy will hunt down a character--", "[enemy]")
{
//    getchar();
    
    srand( (int) time( NULL ) );
    
    DrawEngine de;
    Level* lvl = new Level(&de);

    def_prog_mode();
    endwin();
    
    GIVEN("An enemy is spawn in the level")
    {
        Enemy* evilMonkey = NULL;
        int xpos = 0, ypos = 0;
        
        do{
            xpos = int((float(rand() % 100) / 100) * (lvl->getWidth() - 4) + 1);
            ypos = int((float(rand() % 100) / 100) * (lvl->getHeight() - 4) + 1);
        
        }while ( !lvl->checkMapTileEmpty(xpos, ypos) );

        REQUIRE(lvl->checkMapTileEmpty(xpos, ypos));

        evilMonkey = new Enemy(&de, SPRITE_ENEMY, (float)xpos, float(ypos));

        REQUIRE(evilMonkey->getLives() == 1);
        
//        CHECK(lvl->npc.size() == 0);

        WHEN("it sees a target")
        {
            Character* player = new Character(&de, SPRITE_PLAYER);
            
            evilMonkey->addGoal(player);
            
            REQUIRE(player->getLives() >= 1);
            
            AND_WHEN("it is chasing the goal")
            {
                Sprite* sprite_enemy = evilMonkey;
                
                float oldx = evilMonkey->getX();
                float oldy = evilMonkey->getY();
                
                sprite_enemy->__idleUpdate();

                CAPTURE( evilMonkey->getX() );
                CAPTURE( evilMonkey->getY() );
                
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
                    
                    player = new Mage(&de, SPRITE_PLAYER);

                    player->EvilMonkeys::Sprite::__hookToLevel(lvl);

                    player->__isKeyPressExecuteAction(' ');
                    
                    REQUIRE(lvl->getNumFireballs() > 0);
                    
                    AND_WHEN("i) it got hit by the fireball")
                    {
//                        lvl->addNPC_(sprite_enemy);

                        Fireball* ball = new Fireball(&de, SPRITE_FIREBALL, evilMonkey->getX(), evilMonkey->getY(), 0, 0);
                        
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
                        typename std::list<Sprite *>::const_iterator Iter = lvl->firstNPC();
                        typename std::list<Sprite *>::const_iterator itEnd = lvl->lastNPC();
                        
                        Fireball* theBall = nullptr;
                        
                        for( ; Iter != itEnd; ++Iter )
                        {
                            if ((*Iter)->getClassID() == FIREBALL_CLASSID && lvl->getNumFireballs() == 1) {
                                theBall = (Fireball*)(*Iter);
                                break;
                            }
                        }
                        
                        do{
                            xpos = int((float(rand() % 100) / 100) * (lvl->getWidth() - 4) + 1);
                            ypos = int((float(rand() % 100) / 100) * (lvl->getHeight() - 4) + 1);
                            
                        }while (lvl->checkMapTileEmpty(xpos, ypos));
                        
                        theBall->setPosition(xpos, ypos);
                        theBall->setFacingDirection(0, 0);
                        
                        delete sprite_enemy;
                        sprite_enemy = theBall;
                        
                        sprite_enemy->__idleUpdate();
                        
                        THEN("it should kill itself")
                        {
                            REQUIRE(theBall->getLives() == 0);
                            REQUIRE(lvl->getNumFireballs() == 0);
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
