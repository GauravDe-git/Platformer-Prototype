#include "game.h"

#include <iostream>

#include "Bomb.h"
#include "PhysicsComponent.h"
#include "surface.h"

namespace Tmpl8
{
	void Game::Init()
	{
		player = new Player("assets/player_idle.png", "assets/player_run.png", "assets/player_jump.png", 100,100);
		entities.push_back(player);

		level = new Level("assets/map.png", "assets/foreground.png");
		entities.push_back(level);

        platform = new Platform("assets/platform1.png", 250, 350);
		entities.push_back(platform);

		enemy = new Enemy("assets/enemy_idle.png","assets/enemy_hurt.png", 390, 100);
		entities.push_back(enemy);
	}

	void Game::Shutdown()
	{
		delete player;
		delete level;
		delete platform;
		delete enemy;
	}

    void Game::HandleCollision(Entity* entity, const vec2& oldPosition, vec2& newPosition, float& velocity, bool isXAxis)
    {
        if (const ColliderComponent* entityCollider = entity->GetComponent<ColliderComponent>())
        {
            for (Entity* otherEntity : entities)
            {
                // Skip collision check with self
                if (entity == otherEntity) continue;

                if (const ColliderComponent* otherCollider = otherEntity->GetComponent<ColliderComponent>())
                {
                    // Get the position of the other entity
                    const vec2 otherPosition = otherEntity->GetComponent<Transform2DComponent>()->position;

                    for (auto& bound : entityCollider->bounds)
                    {
                        Bounds offsetBounds = bound;
                        offsetBounds.min += newPosition;
                        offsetBounds.max += newPosition;

                        for (auto& otherBound : otherCollider->bounds)
                        {
                            // Offset the other entity's bounds by its position
                            Bounds offsetOtherBound = otherBound;
                            offsetOtherBound.min += otherPosition;
                            offsetOtherBound.max += otherPosition;

                            if (Bounds::Collides(offsetBounds, offsetOtherBound))
                            {
                                // Collision detected, revert the position and stop the velocity
                                if (isXAxis)
                                {
                                    newPosition.x = oldPosition.x;
                                }
                                else  // Y axis
                                {
                                    newPosition.y = oldPosition.y;
                                    velocity = 0.0f;
                                    Player* player = dynamic_cast<Player*>(entity);
                                    if (player)
                                    {
                                        player->jumping = false;  // Set jumping to false when a collision with the ground is detected
                                    }
                                }
                                return;
                            }
                        }
                    }
                }
            }
        }
    }



    void Game::Tick(float deltaTime)
    {
        //convert dT to seconds
        deltaTime /= 1000;

        // clear the graphics window
        screen->Clear(0);

        level->Draw(screen);

        // Update and draw all entities
        for (Entity* entity : entities)
        {
            TimerComponent* timer = entity->GetComponent<TimerComponent>();
            if (timer)
            {
                timer->timer.Tick();
            }

            PhysicsComponent* physics = entity->GetComponent<PhysicsComponent>();
            Transform2DComponent* transform = entity->GetComponent<Transform2DComponent>();

            if (physics && transform)
            {
                Player* player = dynamic_cast<Player*>(entity);
                SpriteComponent* sprite;
                if (player)
                {
                    if (player->jumping)
                    {
                        sprite = player->GetComponent<JumpingComponent>()->sprite;
                    }
                    else if (physics->velocity.x != 0)
                    {
                        sprite = player->GetComponent<RunningComponent>()->sprite;
                    }
                    else
                    {
                        sprite = player->GetComponent<IdleComponent>()->sprite;
                    }
                    sprite->Update(deltaTime);
                    sprite->Draw(screen, transform->position.x, transform->position.y, 1.0f, player->flip);
                }

                Enemy* enemy = dynamic_cast<Enemy*>(entity);
                if (enemy)
                {
                    SpriteComponent* sprite;
                    if (enemy->hurt)
                    {
                        sprite = enemy->GetComponent<HurtComponent>()->sprite;
                        HurtComponent* hurtComponent = enemy->GetComponent<HurtComponent>();
                        hurtComponent->timer.Tick();
                        // If the timer has reached the hurt time
                        if (hurtComponent->timer.TotalTimeSeconds() >= 1)  // Adjust this value as needed
                        {
                            enemy->hurt = false;  // Change the enemy's state back to not hurt
                        }
                        sprite = hurtComponent->sprite;
                    }
                    else
                    {
                        sprite = enemy->GetComponent<EnemyIdleComponent>()->sprite;
                    }
                    sprite->Update(deltaTime);
                    sprite->Draw(screen, transform->position.x, transform->position.y, 1.0f);
                }

                physics->Update(deltaTime);
                const vec2 oldPosition = transform->position;

                // Add Gravity ,Check for Y collision with all entities
                transform->position.y += physics->velocity.y * deltaTime;
                HandleCollision(entity, oldPosition, transform->position, physics->velocity.y, false);

                // Add horizontal movement ,Check for X collision with all entities
                transform->position.x += physics->velocity.x * deltaTime;
                HandleCollision(entity, oldPosition, transform->position, physics->velocity.x, true);
            }

            // Check if the entity is a bomb
            Bomb* bomb = dynamic_cast<Bomb*>(entity);
            if (bomb)
            {
                TimerComponent* timer = bomb->GetComponent<TimerComponent>();
                SpriteComponent* sprite;
                if (bomb->active)
                {
                    // If the timer has reached the explosion time
                    if (timer->timer.TotalTimeSeconds() >= 3)
                    {
                        bomb->active = false;  // Change the bomb's state to exploding
                    }
                    sprite = bomb->GetComponent<BombIdleComponent>()->sprite;
                }
                else
                {
                    sprite = bomb->GetComponent<BombExplodingComponent>()->sprite;
                    for (Entity* otherEntity : entities)
                    {
                        // If the other entity is an enemy
                        Enemy* enemy = dynamic_cast<Enemy*>(otherEntity);
                        if (enemy)
                        {
                            // Get the positions of the bomb and the enemy
                            vec2 bombPos = bomb->GetComponent<Transform2DComponent>()->position;
                            vec2 enemyPos = enemy->GetComponent<Transform2DComponent>()->position;

                            // Calculate the distance between the bomb and the enemy
                            float dx = bombPos.x - enemyPos.x;
                            float dy = bombPos.y - enemyPos.y;
                            float distance = sqrt(dx * dx + dy * dy);
                            std::cout << "Distance: " << distance << '\n';
                            // If the distance between the bomb and the enemy is less than the explosion radius
                            if (distance < 70)
                            {
                                enemy->hurt = true;
                                HurtComponent* hurtComponent = enemy->GetComponent<HurtComponent>();
                                hurtComponent->timer.Reset();  // Start the timer
                            }
                        }
                    }
                    // If the explosion animation has finished
                    if (sprite->spriteAnim.GetCurrentFrame() >= 8)
                    {
                        // Remove the bomb
                        std::erase(entities, entity);
                        delete entity;
                        continue;  // Skip the rest of the loop for this entity
                    }
                }
                sprite->Update(deltaTime);
                sprite->Draw(screen, transform->position.x, transform->position.y, 1.0f);
            }

            renderSystem.Update(*entity, *screen);
        }
    }


	void Game::KeyUp(SDL_Scancode key) 
	{
		// Get the player's physics component
		PhysicsComponent* physics = player->GetComponent<PhysicsComponent>();

		// Check which key was released and stop the player's movement
		switch (key)
		{
		case SDL_SCANCODE_LEFT:  // Stop moving left
		case SDL_SCANCODE_RIGHT:  // Stop moving right
			physics->velocity.x = 0.0f;
			break;
		default:
			break;
		}
	}


	void Game::KeyDown(SDL_Scancode key) 
	{
		// Get the player's physics component
		PhysicsComponent* physics = player->GetComponent<PhysicsComponent>();

		// Check which key was pressed and adjust the player's velocity
		switch (key)
		{
		case SDL_SCANCODE_LEFT:  // Move left
			physics->velocity.x = -100.0f;
			player->flip = true;
			break;
		case SDL_SCANCODE_RIGHT:  // Move right
			physics->velocity.x = 100.0f;
			player->flip = false;
			break;
		case SDL_SCANCODE_SPACE:  // Jump
			if (!player->jumping)  // Only allow a jump if the player is not already jumping
			{
				physics->velocity.y = -380.0f;  // Apply an upward force
				player->jumping = true;  // Set jumping to true
			}
            break;
        case SDL_SCANCODE_B:  // Drop bomb
        {
            TimerComponent* timer = player->GetComponent<TimerComponent>();

            // Only allow a bomb to be dropped if enough time has passed
            if (timer->timer.TotalTimeSeconds() >= 4)
            {
                // Reset the timer
                timer->timer.Reset();

                float bombPosX;
                if (player->flip)
                {
                    // If the player is facing left, instantiate the bomb to the player's left
                    bombPosX = player->GetComponent<Transform2DComponent>()->position.x - 60.f;
                }
                else
                {
                    // If the player is facing right, instantiate the bomb to the player's right
                    bombPosX = player->GetComponent<Transform2DComponent>()->position.x + 30.f;
                }

                Bomb* bomb = new Bomb("assets/bomb.png", "assets/explode.png", bombPosX, player->GetComponent<Transform2DComponent>()->position.y - 60.f);
                TimerComponent* timer = bomb->GetComponent<TimerComponent>();
                timer->timer.Reset();  // Start the timer
                entities.push_back(bomb);
            }
            break;
        }
		default:
			break;
		}
	}

};