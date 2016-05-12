//
//  enemy.h
//  3dbuzz
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#ifndef enemy_h
#define enemy_h

#include "sprite.hpp"

class Level;
class Character;

class Enemy : public Sprite
{
public:
    Enemy(Level *l, DrawEngine *de, int sprite_index, float xpos, float ypos, int i_lives = 1);
    
    void addGoal(Character* g){ goal = g; }
    
private:
    
    bool move(float xDir, float yDir);
    
    void idleUpdate(void);
    void simulateAI(void);
    
    Character* goal = NULL;
};

#endif /* enemy_h */
