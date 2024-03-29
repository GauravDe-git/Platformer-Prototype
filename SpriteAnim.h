#pragma once

#include "surface.h"

class SpriteAnim
{
public:
    SpriteAnim() = default;
    SpriteAnim(Tmpl8::Sprite* sprite, float fps = 30.0f);

    void Update(float deltaTime)
    {
        totalTime += deltaTime;
    }

    void Draw(Tmpl8::Surface* target, int x, int y, float alpha,bool flip) const;

    unsigned int GetCurrentFrame() const
    {
        if (sprite)
        {
            return static_cast<unsigned int>(totalTime * fps) % sprite->Frames();
        }

        return 0;
    }

    bool IsFinished() const
    {
        if (sprite)
        {
            float duration = sprite->Frames() / fps;
            return totalTime >= duration;
        }

        return false;
    }


private:
    Tmpl8::Sprite* sprite = nullptr;
    float fps = 30.0f;
    float totalTime = 0.0f;
};

