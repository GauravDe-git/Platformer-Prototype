#pragma once
#include "Level.h"
#include "Player.h"
#include "RenderSystem.h"

#include <SDL_scancode.h>

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp(SDL_Scancode key) ;
	void KeyDown(SDL_Scancode key) ;
private:
	Surface* screen;
	Player* player;
	RenderSystem renderSystem;
	std::vector<Entity*> entities;

	Level* level;
};

}; // namespace Tmpl8