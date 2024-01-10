#pragma once
#include "Bomb.h"
#include "Bounds.h"
#include "ColliderComponent.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "Transform2DComponent.h"

class IdleComponent : public Component
{
public:
    SpriteComponent* sprite;

    IdleComponent(const char* filename, int numFrames, float fps = 30.0f)
        : sprite(new SpriteComponent(filename, numFrames, fps, true)) {}
};

class RunningComponent : public Component
{
public:
    SpriteComponent* sprite;

    RunningComponent(const char* filename, int numFrames, float fps = 30.0f)
        : sprite(new SpriteComponent(filename, numFrames, fps, true)) {}
};

class JumpingComponent : public Component
{
public:
    SpriteComponent* sprite;

    JumpingComponent(const char* filename, int numFrames, float fps = 30.0f)
        : sprite(new SpriteComponent(filename, numFrames, fps, true)) {}
};


class Player : public Entity
{
public:
    bool flip;
    bool jumping;
    Player(const char* idleFilename, const char* runningFilename, const char* jumpingFilename,
        float initialX = 0.0f, float initialY = 0.0f, float fps = 20.0f, bool isAnimated = true)
        : flip(false), jumping(false)
    {
        AddComponent(new Transform2DComponent());
        GetComponent<Transform2DComponent>()->position.x = initialX;
        GetComponent<Transform2DComponent>()->position.y = initialY;

        AddComponent(new IdleComponent(idleFilename, 26, fps));
        AddComponent(new RunningComponent(runningFilename, 14, fps));
        AddComponent(new JumpingComponent(jumpingFilename, 7, 5));

        std::vector<Bounds> playerBounds = { Bounds(Tmpl8::vec2(11, 10), Tmpl8::vec2(45, 57)) };
        AddComponent(new ColliderComponent(playerBounds));

        AddComponent(new PhysicsComponent());
        AddComponent(new TimerComponent());
    }
};


