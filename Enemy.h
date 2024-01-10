#pragma once
#include "Bounds.h"
#include "ColliderComponent.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "Transform2DComponent.h"

class EnemyIdleComponent : public Component
{
public:
    SpriteComponent* sprite;

    EnemyIdleComponent(const char* filename, int numFrames, float fps = 20.0f)
        : sprite(new SpriteComponent(filename, numFrames, fps, true)) {}
};

class HurtComponent : public Component
{
public:
    SpriteComponent* sprite;
    Timer timer;

    HurtComponent(const char* filename, int numFrames, float fps = 20.0f)
        : sprite(new SpriteComponent(filename, numFrames, fps, true)) {}
};


class Enemy : public Entity
{
public:
    bool flip;
    bool hurt;
	Enemy(const char* idleFilename, const char* hurtFilename,
        float initialX = 0.0f, float initialY = 0.0f, float fps = 20.0f, bool isAnimated = true)
        : flip(false),hurt(false)
    {
        AddComponent(new Transform2DComponent());
        GetComponent<Transform2DComponent>()->position.x = initialX;
        GetComponent<Transform2DComponent>()->position.y = initialY;

        AddComponent(new EnemyIdleComponent(idleFilename, 34, fps));
        AddComponent(new HurtComponent(hurtFilename, 8, fps));

        std::vector<Bounds> enemyBounds = { Bounds(Tmpl8::vec2(15, 10), Tmpl8::vec2(61, 64)) };
        AddComponent(new ColliderComponent(enemyBounds));

        AddComponent(new PhysicsComponent());
    }
};