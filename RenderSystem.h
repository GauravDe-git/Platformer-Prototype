#pragma once
#include "Entity.h"
#include "SpriteComponent.h"
#include "Transform2DComponent.h"

class RenderSystem
{
public:
    void Update(Entity& entity, Tmpl8::Surface& screen)
    {
        Transform2DComponent* transform = entity.GetComponent<Transform2DComponent>();
        SpriteComponent* sprite = entity.GetComponent<SpriteComponent>();
        ColliderComponent* collider = entity.GetComponent<ColliderComponent>();

        if (transform && sprite)
        {
            Player* player = dynamic_cast<Player*>(&entity);
            bool flip = player ? player->flip : false;
            sprite->Draw(&screen, transform->position.x, transform->position.y, 1.0f, flip);
        }

        if (collider)
        {
            for (auto& bound : collider->bounds)
            {
                Bounds offsetBounds = bound;
                offsetBounds.min += transform->position;
                offsetBounds.max += transform->position;
#ifdef _DEBUG
                if (collider)
                {
                    collider->Draw(&screen, 0xff0000, transform->position);  // Draw the collider in red
                }
                // Draw the collider in red
#endif
                offsetBounds.min -= transform->position;
                offsetBounds.max -= transform->position;
            }
        }
    }
};


