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
        std::vector<Bounds> levelBounds = { Bounds(Tmpl8::vec2(1, 449), Tmpl8::vec2(639, 511)),
                                            Bounds(Tmpl8::vec2(1, 1), Tmpl8::vec2(639, 62)),
                                            Bounds(Tmpl8::vec2(1, 61), Tmpl8::vec2(63, 448)),
                                            Bounds(Tmpl8::vec2(577, 63), Tmpl8::vec2(639, 446)),
                                            Bounds(Tmpl8::vec2(320, 321), Tmpl8::vec2(575, 455)),
                                            Bounds(Tmpl8::vec2(321, 258), Tmpl8::vec2(447, 322)),/* add more Bounds here */ };
        AddComponent(new ColliderComponent(levelBounds));
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


