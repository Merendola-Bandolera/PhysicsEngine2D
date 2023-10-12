#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModulePlayer::~ModulePlayer()
{
	x = 0;
	y = 0;
	xVelocity = 0;
	yVelocity = 0;
	xAcceleration = 0;
	yAcceleration = 0;
	mass = 1.0;
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_LEFT) {
					xAcceleration = -0.1;
					xVelocity = -1.0;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					xAcceleration = 0.1;
					xVelocity = 1.0;
				}
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
					xAcceleration = 0.0;

				}
				break;
			default:
				break;

		}
	}
	xVelocity += xAcceleration;
	xVelocity *= 0.9;
	x += xVelocity;
	y += xVelocity;
	return UPDATE_CONTINUE;
}



