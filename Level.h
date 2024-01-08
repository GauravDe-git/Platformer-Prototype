#pragma once
#include "Bounds.h"
#include "ColliderComponent.h"
#include "Entity.h"
#include "surface.h"
#include "template.h"
#include "Transform2DComponent.h"

class Level : public Entity
{
public:
    Level(const char* backgroundFile, const char* foregroundFile)
        : bg(new Tmpl8::Sprite(new Tmpl8::Surface(backgroundFile), 1)),
        fg(new Tmpl8::Sprite(new Tmpl8::Surface(foregroundFile), 1))
    {
        AddComponent(new Transform2DComponent());
        // Add colliders for the solid areas
        AddComponent(new ColliderComponent(Bounds(Tmpl8::vec2(1, 449), Tmpl8::vec2(639, 511))));
    }

    void Draw(Tmpl8::Surface* screen)
    {
        bg->Draw(screen, 0, 0, 1.0f, false);
        fg->Draw(screen, 0, 0, 1.0f, false);
    }

private:
    Tmpl8::Sprite* bg;
    Tmpl8::Sprite* fg;
};


