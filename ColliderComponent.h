#pragma once
#include <vector>

#include "Bounds.h"
#include "Component.h"
#include "surface.h"

class ColliderComponent : public Component
{
public:
    std::vector<Bounds> bounds;
    bool isTrigger;

    ColliderComponent(const std::vector<Bounds>& bounds, bool isTrigger = false)
        : bounds(bounds), isTrigger(isTrigger)
    {}

    void Draw(Tmpl8::Surface* target, Tmpl8::Pixel color, const Tmpl8::vec2& position) const
    {
        for (const auto& bound : bounds)
        {
            Bounds offsetBounds = bound;
            offsetBounds.min += position;
            offsetBounds.max += position;
            target->Box(offsetBounds.Left(), offsetBounds.Top(), offsetBounds.Right(), offsetBounds.Bottom(), color);
        }
    }
};

