//
//  character.hpp
//  evil-monkeys
//
//  Created by phuong on 5/11/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef character_hpp
#define character_hpp

#include "sprite.hpp"

class Character : public Sprite
{
public:
    Character(Level *l, DrawEngine *de, int s_index, float xpos = 1, float ypos = 1,
              int lives = 3, int up_key = KEY_UP, int down_key = KEY_DOWN,
              int left_key = KEY_LEFT, int right_key = KEY_RIGHT);
    ~Character();
    
    virtual bool keyPress(int key);
    
protected:
    int upKey, downKey, rightKey, leftKey;
    
private:
    Level *level;
    
};

#endif /* character_hpp */
