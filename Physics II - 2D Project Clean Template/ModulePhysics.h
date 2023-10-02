#pragma once
#include "Module.h"
#include "Globals.h"
#include "Application.h"

class ModulePhysics : public Module
{
public:

	struct Vector2D 
	{
		float x;
		float y;
	};

	Vector2D GetVector(float ix, float iy, float fx, float fy)
	{
		Vector2D vectordir;

		float squarert;

		vectordir.x = fx - ix;
		vectordir.y = fx - iy;

		squarert = sqrt(vectordir.x * vectordir.x + vectordir.y * vectordir.y);
		
		vectordir.x = vectordir.x / squarert;
		vectordir.y = vectordir.y / squarert;

		return vectordir;
	}
	
	
	
		
		
	
	float GetAngle() 
	{
		
	}

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
		Vector2D force;
		SDL_Rect rect;
		float time = 1;
		float fps;
		Uint64 NOW = SDL_GetTicks();
		Uint64 LAST = 0;
		double deltaTime = 0;
		float dummy;

		void xMovement() 
		{
			dummy = 8 * cos(45);

			if (dummy < 0)
				dummy *= -1;

			x = x + dummy;
			
			
			/*if (force.x != 0)
				force.x -= 0.1f;*/
		}
		
		double GetDelta() {
			LAST = NOW;
			NOW = SDL_GetTicks();
			deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetTicks());

			return deltaTime;
		}

		void Gravity() 
		{
			time += 0.01f;
				
			fps = 8 *sin(45);
			//y = 3*sin(atan2(3, 4)) + 1/2*gravity*time*time;
			if (fps < 0)
				fps *= -1;

			y += -fps +  -gravity * time;
			//y -= 10 + gravity * GetDelta();
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
	int mousex;
	int mousey;
	Vector2D bector;
	bool isLaunched;

	
};