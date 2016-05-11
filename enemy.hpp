//
//  enemy.hpp
//  evil-monkeys
//
//  Created by phuong on 5/11/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef enemy_hpp
#define enemy_hpp

#include "character.hpp"

class Level;
class Character;

class Enemy : public Sprite
{
public:
    Enemy(Level *l, DrawEngine *de, int s_index, float x = 1, float y = 1, int i_lives = 1);
    
    bool addGoal(Character *g){ goal = g; return true; }
    bool move(float x, float y);
    
    void idleUpdate(void){
//        if ( goal->isAlive()) simulateAI();
    }
    
protected:
    
    void simulateAI(void);
    Character *goal;
    
private:
    
};

#endif /* enemy_hpp */
