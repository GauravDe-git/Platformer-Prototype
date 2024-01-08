#pragma once
#include "Bounds.h"
#include "ColliderComponent.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "Transform2DComponent.h"

class Player : public Entity
{
public:
    bool flip;
    bool jumping;
    Player(const char* filename, int numFrames, float initialX = 0.0f, float initialY = 0.0f, float fps = 20.0f, bool isAnimated = true)
	    :flip(false), jumping(false) 
    {
        AddComponent(new Transform2DComponent());
        GetComponent<Transform2DComponent>()->position.x = initialX;
        GetComponent<Transform2DComponent>()->position.y = initialY;

        AddComponent(new SpriteComponent(filename, numFrames, fps, isAnimated));

        std::vector<Bounds> playerBounds = { Bounds(Tmpl8::vec2(11, 10), Tmpl8::vec2(45, 57)) };
        AddComponent(new ColliderComponent(playerBounds));

        AddComponent(new PhysicsComponent());
    }
};

