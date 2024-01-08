#include "game.h"

#include "PhysicsComponent.h"
#include "surface.h"

namespace Tmpl8
{
	void Game::Init()
	{
		player = new Player("assets/player_idle.png",26,100,0);
		entities.push_back(player);

		level = new Level("assets/map.png", "assets/foreground.png");
		entities.push_back(level);
	}

	void Game::Shutdown()
	{
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
			SpriteComponent* sprite = entity->GetComponent<SpriteComponent>();
			PhysicsComponent* physics = entity->GetComponent<PhysicsComponent>();
			Transform2DComponent* transform = entity->GetComponent<Transform2DComponent>();
			ColliderComponent* collider = entity->GetComponent<ColliderComponent>();

			if (sprite && transform)
			{
				sprite->Update(deltaTime);
				sprite->Draw(screen, transform->position.x, transform->position.y, 1.0f);
			}
			if (physics)
			{
				physics->Update(deltaTime);
				const vec2 oldPosition = transform->position;

				// Add Gravity 
				transform->position.y += physics->velocity.y * deltaTime;
				// Check for collision with the level
				ColliderComponent* levelCollider = level->GetComponent<ColliderComponent>();
				if (collider && levelCollider && collider->bounds.At(transform->position).Collides(levelCollider->bounds))
				{
					// Collision detected, revert the y position and stop the y velocity
					transform->position.y = oldPosition.y;
					physics->velocity.y = 0.0f;
				}

				// Add horizontal movement
				transform->position.x += physics->velocity.x * deltaTime;
				// Check for collision with the level
				if (collider && levelCollider && collider->bounds.At(transform->position).Collides(levelCollider->bounds))
				{
					// Collision detected, revert the x position
					transform->position.x = oldPosition.x;
				}
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
			break;
		case SDL_SCANCODE_RIGHT:  // Move right
			physics->velocity.x = 100.0f;
			break;
		default:
			break;
		}
	}

};