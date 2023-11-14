#pragma once
#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "Animation.h"

#include "ModuleSceneIntro.h"
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
		int mass;
		int density;
		int surface;
		int CDrag;

		float buoyancy;
		float roce;
		float speed;
		float acceleration;
		float angle;
		Vector2D TotalForce;


		SDL_Rect rect;
		float time;
		float vx, vy, ax, ay;
		bool impliciteuler = false;
		bool symplecticeuler = false;
		bool velocityverlet = false;
		int integrator = 3;



	

		bool Intersects(const SDL_Rect& r) const
		{
			return (rect.x < r.x + r.w &&
				rect.x + rect.w > r.x &&
				rect.y < r.y + r.h &&
				rect.h + rect.y > r.y);
		}

	private:
	
		
	
	};
	void ForceSum(square patata, float gravity, float hydrodinamics, float aerodynamics, float launchforcex, float launchforcey);
	void VelocityVerlet(square obj);
public:
	bool limitFps;
private:
	SDL_Renderer* renderer;
	SDL_Rect rect;
	bool debug;
	square test;
	square floor;
	int mousex;
	int mousey;
	bool isLaunched;
	float playerx;
	float playery;

	float tx;
	float ty;
	float ttime;
	float tvx;
	float tvy;
	float tspeed;
	float tax;
	float tay;
	SDL_Texture* texture;
	SDL_Texture* texture2;
	SDL_Texture* texture3;
	Animation Explosion;
	Animation Ruedas;
	Animation Canon;
	Animation* CurrentAnim;
	bool isSwamp;
	char* integratorName;
	float yMax;
	float dt;



};