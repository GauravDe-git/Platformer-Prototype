# Platformer Prototype /Tmpl8 ++

This game uses a Minimalistic 2D game framework in C++ named as 'The Tmpl8', by BUAS. (BUAS version https://www.buas.nl/games IGAD/BUAS(NHTV)/UU - Jacco Bikker - 2006-2020). 

I have made some further updates to it. 
- Updated to C++ 20 standard, with some bug fixes related to const char*. 
- SDL2 updated to 2.28.5. 
- FreeImage updated to 3.14.

This project is intended to be used to learn to use the Tmpl8 framework and properly use ECS architecture for game development.

The Entity-Component-System (ECS) is a design pattern often used in game development. In this pattern, every object is an Entity, which is a container for Components. Components are data structures that hold state, and Systems are logic that operates on entities that have certain components.

Here’s a high-level overview of the ECS architecture in this project:

### Entity: 
 - A general-purpose object. It doesn’t have any game-specific logic or state. Instead, it’s a container for components. It provides methods to add, get, and remove components.

### Component:
 - A data structure that holds state but doesn’t have any game-specific logic. There are several types of components:

### Transform2DComponent: 
- Holds the position, rotation, and scale of an entity. It also provides a method to translate the entity.

### SpriteComponent: 
- Holds a sprite, a sprite animation, and a flag indicating whether the sprite is animated. It provides methods to update the sprite animation and draw the sprite.

### ColliderComponent: 
- Holds a list of bounds and a flag indicating whether the collider is a trigger. It provides a method to draw the collider.

### PhysicsComponent: 
- Holds the velocity and acceleration of an entity. It provides a method to update the velocity based on the acceleration.

### System: 
- This is where the game-specific logic resides. In the code, currently, the systems are not explicitly defined as classes, but they exist conceptually. For example, the code that updates and draws all entities in the Tick function could be considered a system.

Here’s how these concepts relate to each other:

An Entity can have multiple Components. For example, an enemy entity might have a Transform2DComponent, a SpriteComponent, and a PhysicsComponent. A Component belongs to one Entity. For example, a SpriteComponent might belong to an enemy entity.A System operates on Entities that have certain Components. For example, a physics system might operate on all entities with a PhysicsComponent and a Transform2DComponent.

#### Future refactoring plans for System:
The current implementation of the Tick function in the Game class is handling a lot of responsibilities, including updating and drawing entities, handling physics, and managing game-specific logic. While this might work for a small game, it can become difficult to manage as the game grows in complexity.

Refactoring the code to encapsulate game-specific logic into separate systems can make the code more modular, easier to understand, and simpler to maintain. 

- PhysicsSystem: This system could handle updating the physics of all entities that have a PhysicsComponent. The gravity and collision logic currently in the Tick function could be moved here.
- RenderSystem: This system could handle drawing all entities that have a SpriteComponent. The logic for updating and drawing sprites currently in the Tick function could be moved here.
- BombSystem: This system could handle the logic specific to bombs, such as checking if a bomb is active, handling explosions, and deleting bombs. The bomb-specific logic currently in the Tick function could be moved here.
- EnemySystem: This system could handle the logic specific to enemies, such as changing the enemy’s sprite based on its state. The enemy-specific logic currently in the Tick function could be moved here.

## Credits:
Pixel Bomb asset pack by Pixel Frog.
