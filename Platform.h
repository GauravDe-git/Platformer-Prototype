#pragma once
#include "ColliderComponent.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "Transform2DComponent.h"

class Platform : public Entity
{
public:
    Platform(const char* filename, float initialX = 0.0f, float initialY = 0.0f)
    {
        AddComponent(new Transform2DComponent());
        GetComponent<Transform2DComponent>()->position.x = initialX;
        GetComponent<Transform2DComponent>()->position.y = initialY;

        AddComponent(new SpriteComponent(filename, 1, 30.0f, false));

        std::vector<Bounds> platformBounds = { Bounds(Tmpl8::vec2(1, 0), Tmpl8::vec2(62, 9)) };
        AddComponent(new ColliderComponent(platformBounds));
    }
};
