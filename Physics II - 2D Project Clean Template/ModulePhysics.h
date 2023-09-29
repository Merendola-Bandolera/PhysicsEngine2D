#pragma once
#include "Module.h"
#include "Globals.h"

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
	

		void xMovement() 
		{
		

			x = x + force.x;
			
			/*if (force.x != 0)
				force.x -= 0.1f;*/
		}
		
		void Gravity() 
		{
			force.y -= gravity;
			y = y + force.y;
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
};