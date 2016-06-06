//
//  enemy.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "level.h"

using namespace EvilMonkeys;

bool Enemy::__move(float xDir, float yDir)
{
    int xpos = (int)(getX() + xDir);
    int ypos = (int)(getY() + yDir);

    if (isValidLevelMove(xpos, ypos)) {

        facingDirection_.x = xDir;
        facingDirection_.y = yDir;

        // make sure we don't run into any other enemies;
        // not yet support early break or skip out element with range-for
        for( auto& NPC : level_->NPC() )
            if ( NPC->is(ENEMY_CLASSID) && NPC != this )
                if ( NPC->matchCurrentLocation(xpos, ypos) )
                    return false;

        erase_();

        setPosition(getX() + xDir, getY() + yDir);

        draw_();

        // hit and kill the player
        if ( this->hits(goal_) )
            goal_->__addLives(-1);

        return true;
    }

    return false;
}

void Enemy::__addLives(int num)
{
    Sprite::__addLives(num);

    //transform
    setSpriteIndex(drawArea_->registerSprite(SPRITE_ENEMY_1, '$', RED_BLACK));
}

bool Enemy::__hookToLevel(Level* lvl, bool draw_at_once)
{
    if (Sprite::__hookToLevel(lvl, draw_at_once))
    {
        addGoal(level_->player());

        return true;
    }

    return false;
}

void Enemy::__idleUpdate()
{
    if (goal_->getLives() > 0)
        simulateAI_();
}

void Enemy::simulateAI_(void)
{
    vector goal_pos = goal_->getPosition();

    if ( this->hits(goal_) )
        __move(0, 0);

    vector direction;

    direction.x = goal_pos.x - getX();
    direction.y = goal_pos.y - getY();

    float mag = sqrt(direction.x * direction.x + direction.y * direction.y);

    direction.x = direction.x / (mag * 6);
    direction.y = direction.y / (mag * 6);

    if ( level_->checkMapTileEmpty( 0, (int)lround(direction.y) ) || level_->checkMapTileEmpty( (int)lround(direction.x), 0 ) )
    {
        if (!__move(direction.x, direction.y))
            if (!__move(0, float(rand() % 3 - 1)))
                __move(float(rand() % 3 - 1), 0);

    }
    else
    {
        if (!__move(0, direction.y))
            if (!__move(0, float(rand() % 3 - 1)))
                __move(float(rand() % 3 - 1), 0);


        if (!__move(direction.x, 0))
            if (!__move(0, float(rand() % 3 - 1)))
                __move(float(rand() % 3 - 1), 0);
        
    }
    
}