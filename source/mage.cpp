//
//  mage.cpp
//  Evil Monkey Game
//
//  Created by phuong on 1/28/16.
//  Copyright © 2016 phuong. All rights reserved.
//

#include "mage.h"

#include "level.h"
#include "fireball.h"
#include "bomb.h"

using namespace EvilMonkeys;

Mage::Mage(DrawEngine *de, int sprite_index, float xpos, float ypos,
           int lives, char spellK, char reloadK, char bombK, int up_key, int down_key, int left_key, int right_key) : Character(de, sprite_index, xpos, ypos, lives, up_key, down_key, left_key, right_key)
{
    spellKey = spellK;
    bombKey = bombK;
    reloadKey = reloadK;
    setClassID(MAGE_CLASSID);
}

bool Mage::__isKeyPressExecuteAction(int key)
{
    if (!Character::__isKeyPressExecuteAction(key))
    {
        if (key == spellKey)
        {
            if (level->getLastTimeReload() != 0 && level->getElapsedTime() - level->getLastTimeReload() < COOL_DOWN_RELOAD_IN_MILISECOND)
                return false;

            if(level->getNumFireballs() > 0)
            {
                typename std::list<Sprite *>::const_iterator Iter = level->firstNPC();
                typename std::list<Sprite *>::const_iterator itEnd = level->lastNPC();

                for( ; Iter != itEnd; ++Iter )
                    if ( (*Iter)->getClassID() == FIREBALL_CLASSID )
                    {
                        if ( (*Iter)->matchCurrentFacingDir(facingDirection.x, facingDirection.y) )
                        {
                            if (level->getNumFireballs() < ammoCartridge)
                                return castSpell_();
                            else
                                return false;
                        }
                        else
                        {
                            return false;
                        }
                    }
            }


            if (level->getNumFireballs() < ammoCartridge)
                return castSpell_();
            else
                return false;

        }

        if (key == reloadKey) {
            level->setLastTimeReload(level->getElapsedTime());
            return reload_();
        }

        if (key == bombKey) {
            if( level->getMaxBombsAllow() - level->getNumBombs() < 1 )
                return false;

            return castBomb_();
        }
    }
    return true;
}

bool Mage::castBomb_()
{
    if( level->spawnNPC( drawArea->registerSprite(SPRITE_BOMB), -1, int(getX() - facingDirection.x), int(getY() - facingDirection.y) ) )
    {
        level->updateNumBombs(1);
        return true;
    }

    return false;
}

bool Mage::reload_()
{

    ammoCartridge = FULL_AMMO;

    return true;
}

bool Mage::castSpell_()
{
    if ( (facingDirection.x == 0 && facingDirection.y == -1) || (facingDirection.x == 0 && facingDirection.y == 1) ) {
        drawArea->registerSprite(SPRITE_FIREBALL, '|');
    }
    if ( (facingDirection.x == -1 && facingDirection.y == 0) || (facingDirection.x == 1 && facingDirection.y == 0) ) {
        drawArea->registerSprite(SPRITE_FIREBALL, '-');
    }

    if ( level->spawnNPC( drawArea->registerSprite(SPRITE_FIREBALL), -1, int(getX() + facingDirection.x), int(getY() + facingDirection.y), facingDirection.x, facingDirection.y ) )
    {
        level->updateNumFireballs(1);
        updateAmmoCartridge(-1);
        return true;
    }
    
    return false;
}