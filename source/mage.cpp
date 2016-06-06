//
//  mage.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "level.h"

namespace Target {

    using namespace EvilMonkeys;

    bool Mage::__isKeyPressExecuteAction(int key)
    {
        if (!Character::__isKeyPressExecuteAction(key))
        {
            if (key == spellKey_)
            {
                if (level_->getLastTimeReload() != 0 && level_->getElapsedTime() - level_->getLastTimeReload() < COOL_DOWN_RELOAD_IN_MILISECOND)
                    return false;

                if( level_->getNumFireballs() > 0 )
                {
                    for( auto& Iter : level_->NPC() )
                        if ( Iter->is(FIREBALL_CLASSID) && Iter->matchCurrentFacingDir() )
                            return castSpell_();

                    return false;
                }

                return castSpell_();
            }

            if (key == reloadKey_) {
                level_->setLastTimeReload(level_->getElapsedTime());
                return ammoCartridge_ = FULL_AMMO;
            }

            if (key == bombKey_) {
                if( level_->getMaxBombsAllow() - level_->getNumBombs() < 1 )
                    return false;

                return level_->spawnNPC( drawArea_->registerSprite(SPRITE_BOMB), -1, int(getX() - facingDirection_.x), int(getY() - facingDirection_.y) );
            }
        }
        return true;
    }

    bool Mage::castSpell_()
    {
        vector left {-1, 0};
        vector right {1, 0};
        vector up {0, -1};
        vector down {0, 1};

        if ( matchCurrentFacingDir(up) || matchCurrentFacingDir(down) )
            drawArea_->registerSprite(SPRITE_FIREBALL, '|');

        if ( matchCurrentFacingDir(left) || matchCurrentFacingDir(right) )
            drawArea_->registerSprite(SPRITE_FIREBALL, '-');

        if (level_->getNumFireballs() < ammoCartridge_)
            return level_->spawnNPC(drawArea_->registerSprite(SPRITE_FIREBALL), -1, int(getX() + facingDirection_.x), int(getY() + facingDirection_.y), facingDirection_.x, facingDirection_.y);

        return false;
    }

}