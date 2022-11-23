#include "Animator.hpp"

spic::Animator::Animator(const int fps) 
    : fps{fps}
    , freeze {false}
    , index{0}
    , looping{false}
{
}

const void spic::Animator::Freeze()
{
    freeze = true;
}

const bool spic::Animator::IsFozen() const
{
    return this->freeze;
}

void spic::Animator::Stop()
{
    freeze = false;
    index = 0;
    looping = false;
}

void spic::Animator::AddSprite(const std::shared_ptr<Sprite> sprite)
{
    this->sprites.push_back(sprite);
}

const std::vector<std::shared_ptr<spic::Sprite>> spic::Animator::Sprites() const
{
    return this->sprites;
}

const int spic::Animator::Fps() const
{
    return this->fps;
}

const void spic::Animator::Fps(const int fps)
{
    this->fps = fps;
}

const bool spic::Animator::Looping() const
{
    return this->looping;
}

const int spic::Animator::Index() const
{
    return this->index;
}

const void spic::Animator::Index(const int index)
{
    this->index = index;
}
