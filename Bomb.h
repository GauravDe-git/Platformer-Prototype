#pragma once
#include "Entity.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "Timer.h"
#include "Transform2DComponent.h"


class TimerComponent : public Component
{
public:
    Timer timer;
};

class BombIdleComponent : public Component
{
public:
    SpriteComponent* sprite;

    BombIdleComponent(const char* filename, int numFrames, float fps = 30.0f)
        : sprite(new SpriteComponent(filename, numFrames, fps, true)) {}
};

class BombExplodingComponent : public Component
{
public:
    SpriteComponent* sprite;

    BombExplodingComponent(const char* filename, int numFrames, float fps = 30.0f)
        : sprite(new SpriteComponent(filename, numFrames, fps, true)) {}
};

class Bomb : public Entity
{
public:
    bool active;

    Bomb(const char* idleFilename, const char* explodingFilename, float initialX = 0.0f, float initialY = 0.0f)
        :active(true)
    {
        AddComponent(new Transform2DComponent());
        GetComponent<Transform2DComponent>()->position.x = initialX;
        GetComponent<Transform2DComponent>()->position.y = initialY;

        AddComponent(new BombIdleComponent(idleFilename, 10, 20.0f));
        AddComponent(new BombExplodingComponent(explodingFilename, 9, 20.0f));

        AddComponent(new PhysicsComponent());
        AddComponent(new TimerComponent());

        std::vector<Bounds> bombBounds = { Bounds(Tmpl8::vec2(32, 49), Tmpl8::vec2(61, 86)) };
        AddComponent(new ColliderComponent(bombBounds));
    }
};
