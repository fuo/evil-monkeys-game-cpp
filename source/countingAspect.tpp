
// for Bomb
template <class Target>
Counting_Aspect<Target>::Counting_Aspect(DrawEngine *de, int sprite_index, float sprite_xpos, float sprite_ypos)
: Target(de, sprite_index, sprite_xpos, sprite_ypos)
{

}

// for Fireball
template <class Target>
Counting_Aspect<Target>::Counting_Aspect(DrawEngine *de, int sprite_index, float xpos, float ypos, float xDir, float yDir)
: Target(de, sprite_index, xpos, ypos, xDir, yDir)
{

}

// for Mage
template <class Target>
Counting_Aspect<Target>::Counting_Aspect(DrawEngine *de, int sprite_index)
: Target(de, sprite_index)
{

}


template <class Target>
bool Counting_Aspect<Target>::__hookToLevel(Level* lvl, bool draw_at_once)
{
    level_ = lvl;
    hero_ = level_->player();

    auto ret = Target::__hookToLevel(lvl);

    return ret;
}

template <class Target>
void Counting_Aspect<Target>::__addLives(int num)
{
    Target::__addLives(num);

    if (Target::is(BOMB_CLASSID) && Target::hits(hero_))
        level_->updateNumBombs(-1);

    if (Target::is(FIREBALL_CLASSID))
        level_->updateNumFireballs(-1);

    // if (counter_ > 0) --counter_;
}

template <class Target>
bool Counting_Aspect<Target>::__isKeyPressExecuteAction(int key)
{
    auto ret = Target::__isKeyPressExecuteAction(key);

    if (ret && key == 't')
        level_->updateNumBombs(1);

    if (ret && key == ' ')
    {
        level_->updateNumFireballs(1);
        Target::updateAmmoCartridge(-1);
    }

    return ret;
}

template <class Target>
bool Counting_Aspect<Target>::spawnNPC(int sprite_index, int distanceToGoal, int xpos, int ypos, float xface, float yface)
{
    SpawnAction tjp{sprite_index, distanceToGoal, xpos, ypos, xface, yface, false};
    advice(&tjp);

    switch (sprite_index)
    {
        case SPRITE_ENEMY:

            break;

        case SPRITE_BOMB:

            break;

        case SPRITE_FIREBALL:
        {
            //                    tjp = {sprite_index, distanceToGoal, xpos, ypos, xface, yface, false};

            //                    this->updateNumFireballs(1);
            break;
        }

        default:
            return false;
    }

    // ++counter_;

    return tjp.ret;
}

