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
		float acceleration;
		float force;
		SDL_Rect rect;
	

		void xMovement() 
		{
		

			x = x + speed + force;
			
			if (force != 0)
				force -= 0.1f;
		}
		
		void Gravity() 
		{
			y = y - gravity;
		}

		bool Intersects(const SDL_Rect& r) const
		{
			return (rect.x < r.x + r.w &&
				rect.x + rect.w > r.x &&
				rect.y < r.y + r.h &&
				rect.h + rect.y > r.y);
		}

	private:

	
		
	};

	


private:
	SDL_Renderer* renderer;
	SDL_Rect rect;
	bool debug;
	square test;
	square floor;
};