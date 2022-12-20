#include "Animator.hpp"
#include <algorithm>
#include "GeneralHelper.hpp"

spic::Animator::Animator(const int fps) 
    : fps{fps}
    , freeze {false}
    , index{1}
    , looping{false}
    , running{true}
{
}

const void spic::Animator::Freeze()
{
    freeze = true;
}

const bool spic::Animator::IsFrozen() const
{
    return this->freeze;
}

void spic::Animator::InitHorizontalSpriteSheet(const std::string& spriteSheet
    , const int frames, const int width, const int height, const int yOffsett, const int XOffsett)
{
    for (size_t i = 0; i < frames; ++i)
    {
        sprites.emplace_back(std::make_shared<spic::Sprite>(spriteSheet,0, static_cast<int>(i)));
        sprites[i]->Height(height);
        sprites[i]->Width(width);
        sprites[i]->X(width * (static_cast<int>(i) - XOffsett));
        sprites[i]->Y(yOffsett);
    }
}

void spic::Animator::Play(bool loop)
{
    using namespace std::chrono;
    typedef high_resolution_clock Clock;
    Clock::time_point t0 = Clock::now();
    freeze = false;
    looping = { loop };
    running = { true };
}

void spic::Animator::Stop()
{
    freeze = false;
    index = 1;
    lastUpdate = 0;
    looping = false;
    running = false;
}

void spic::Animator::AddSprite(const std::shared_ptr<Sprite> sprite)
{
    this->sprites.push_back(sprite);

    std::sort(sprites.begin(), sprites.end(), spic::helper_functions::general_helper::SpriteSorting);
}

const std::vector<std::shared_ptr<spic::Sprite>> spic::Animator::Sprites() const
{
    return this->sprites;
}

const int spic::Animator::Fps() const
{
    return this->fps;
}

void spic::Animator::Fps(const int fps)
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

void spic::Animator::Index(const int index)
{
    this->index = index;
}

void spic::Animator::IncreaseIndex()
{
    if (++this->index > sprites.back()->OrderInLayer() + 1)
        this->index = 1;
}

bool spic::Animator::IsRunning() const
{
    return this->running;
}

uint64_t spic::Animator::LastUpdate() const
{
    return this->lastUpdate;
}

void spic::Animator::LastUpdate(const uint64_t lastUpdate)
{
    this->lastUpdate = lastUpdate;
}
