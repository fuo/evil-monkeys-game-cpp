//
//  fireball.cpp
//  3dbuzz
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include <list>

#include "fireball.hpp"

Fireball::Fireball(Level *lev, DrawEngine *de, int s_index, float x, float y,
                   float xDir, float yDir, int i_lives) : Sprite(lev, de, s_index, x, y, i_lives)
{
    facingDirection.x = xDir;
    facingDirection.y = yDir;
    
    classID = FIREBALL_CLASSID;
}

void Fireball::idleUpdate()
{
    if (Sprite::move(facingDirection.x, facingDirection.y)) {
        list <Sprite *>::iterator Iter;
        
        for (Iter = level->npc.begin(); Iter != level->npc.end(); Iter++) {
            if ((*Iter)->classID != classID && (int)(*Iter)->getX() == pos.x & (int)(*Iter)->getY() == pos.y) {
                
                // kill the enemy got hit
                (*Iter)->addLives(-1);
                --level->numEnemies;
                
                // kill that firewall itself
                addLives(-1);
            }
        }
    }
    else{
        // hit the wall border
        addLives(-1);
    }
}