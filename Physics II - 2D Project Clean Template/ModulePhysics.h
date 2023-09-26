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

	class square
	{
	public:
		int x;
		int y;
		int w;
		int h;
		int gravity;
		int mass;
		int speed;
		SDL_Rect rect;
	


		
		void Gravity() 
		{
			y = y - gravity;
		}


	private:

	
		
	};

	


private:
	SDL_Renderer* renderer;
	SDL_Rect rect;
	bool debug;
	square test;
};