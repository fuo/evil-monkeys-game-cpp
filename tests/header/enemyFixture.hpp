//
//  enemyFixture.h
//  evil-monkeys
//
//  Created by phuong on 5/14/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef enemyFixture_h
#define enemyFixture_h

#include "enemy.hpp"
#include "drawEngine.hpp"
#include "level.hpp"

using namespace EvilMonkeys;

class EnemyFixture
{
private:
    static int hide;
    
protected:
    DrawEngine de;
    Level* lvl;
    std::list<Sprite*>::iterator enemy;
    
public:
    // setup
    EnemyFixture(){
        lvl = new Level(&de);
        lvl->addEnemies(1);
        enemy = lvl->npc.begin();
    }
    
    // teardown
    ~EnemyFixture(){ }

    
};

#endif /* enemyFixture_h */
