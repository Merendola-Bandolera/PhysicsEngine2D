#pragma once
#include "Module.h"
#include "Globals.h"

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	

	int x;
	int y;
	int gravity;
	int mass;

private:
	SDL_Renderer* renderer;
	SDL_Rect rect;
	bool debug;
};