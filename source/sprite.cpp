//
//  sprite.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/27/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "level.h"

using namespace EvilMonkeys;

bool Sprite::__move(float xDir, float yDir)
{
    vector target;
    
    target.x = pos_.x + xDir;
    target.y = pos_.y + yDir;

    if ( isValidLevelMove(target.x, target.y) )
    {
        // update the facing direction before move
        facingDirection_.x = xDir;
        facingDirection_.y = yDir;

        // erase sprite at current position
        if ( !isNPC_ || level_->checkMapTileEmpty(pos_.x, pos_.y, SPRITE_PLAYER) )
            erase_();

        // update its pos to the target position
        setPosition(target.x, target.y);

        // draw itseft with its new position
        draw_();

        return true;
    }

    return false;
}

void Sprite::draw_(float x, float y){

    if (x < 0)
        x = pos_.x;

    if (y < 0)
        y = pos_.y;

    drawArea_->drawSprite_(spriteIndex_, (int)x, (int)y);
}

void Sprite::erase_(void){
    drawArea_->eraseSprite_((int)pos_.x, (int)pos_.y);

    if(level_ && level_->player() && level_->player()->getLives() > 0 && is(BOMB_CLASSID))
        if(level_->player()->matchCurrentLocation((int)pos_.x, (int)pos_.y))
            level_->player()->draw_();
}

bool Sprite::isValidLevelMove(int xpos, int ypos)
{
    if (!level_)
        return false;

    // check inside level
    if ( level_->checkMapTileEmpty(xpos, ypos) )
        return true;

    return false;
}

bool Sprite::hits(Sprite* other)
{
    return ( !is(other->getClassID()) && other->matchCurrentLocation(pos_.x, pos_.y) );
}

bool Sprite::matchCurrentLocation(int xpos, int ypos)
{
    return ( (int)pos_.x == xpos && (int)pos_.y == ypos );
}

bool Sprite::matchCurrentFacingDir(vector dir)
{
    auto player {level_->player()};

    if (dir.x == 0 && dir.y == 0)
    {
        dir.x = player->getFaceX();
        dir.y = player->getFaceY();
    }

    return ( (int)facingDirection_.x == (int)dir.x && (int)facingDirection_.y == (int)dir.y );
}

bool Sprite::__hookToLevel(Level* lvl, bool draw_at_once)
{
    if (lvl == nullptr)
        return false;

    if (classID_ == FIREBALL_CLASSID)
        draw_at_once = false;

    if (draw_at_once)
        // display itseft to the world right after born
        draw_();

    level_ = lvl;

    if (isNPC_)
        level_->addNPC(this);

    return true;
}