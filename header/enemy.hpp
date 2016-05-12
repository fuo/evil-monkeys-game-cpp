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
#include "drawEngine.hpp"

class Level;
class Character;

class Enemy : public Sprite
{
public:
    Enemy(Level *l, DrawEngine *de, int s_index, float x = 1, float y = 1, int i_lives = 1);
    
    void addGoal(Character *g);
    bool move(float x, float y);
    
    void idleUpdate(void);
    
protected:
    void simulateAI(void);
    Character *goal;
    
};

#endif /* enemy_h */
