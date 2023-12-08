#pragma once
#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleAudio.h"
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
		float hydrodinamics;
		float buoyancy;
		float roce;
		float speed;
		float acceleration;
		float angle;
		Vector2D TotalForce;
		char name;
		bool isSwamp;
		SDL_Rect rect;
		float time;
		float vx, vy, ax, ay;
		bool impliciteuler = false;
		bool symplecticeuler = false;
		bool velocityverlet = false;
		int integrator = 3;
		float jumpcd;
		int hp = 5;
		float fuel = 100;

		bool jumping;
	

		bool Intersects(const SDL_Rect& r) const
		{
			return (rect.x < r.x + r.w &&
				rect.x + rect.w > r.x &&
				rect.y < r.y + r.h &&
				rect.h + rect.y > r.y);
		}

	private:
	
		
	
	};
	void ForceSum(square &obj,  float launchforcex, float launchforcey);
	void VelocityVerlet(square &obj);
	void SymplecticEuler(square &obj);
	void ImplicitEuler(square &obj);
	bool Collide(SDL_Rect& r, SDL_Rect& r2);
	void CollisionResolution(square &obj, SDL_Rect& r);
public:
	bool limitFps;

	double dt;
	float deltaTime;
private:
	SDL_Rect suelo = { 500,300,125,10 };
	SDL_Rect suelo2 = { 0,300,188,10 };
	SDL_Rect suelo3 = { 850,450,188,10 };

	SDL_Rect wall = { 500,310,10,300 };
	SDL_Rect wall3 = { 500,510,10,300 };
	SDL_Rect wall2 = { 1050,0,10,3000 };

	SDL_Rect wall4 = { 178,310,10,300 };
	SDL_Rect wall5 = { 178,510,10,300 };


	SDL_Rect wall6 = { 615,310,10,300 };
	SDL_Rect wall7 = { 615,510,10,300 };

	SDL_Rect wall8 = { 850,460,10,300 };
	SDL_Rect wall9 = { 850,660,10,300 };


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
	bool gravity;
	
	
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
	SDL_Texture* texture4;
	SDL_Texture* texture5;
	SDL_Texture* texture6;
	SDL_Texture* texture7;
	SDL_Texture* texture8;
	SDL_Texture* texture9;
	SDL_Texture* texture10;
	Animation Explosion;
	Animation Ruedas;
	Animation Canon;
	Animation* CurrentAnim;
	//bool isSwamp;
	char* integratorName;
	float force = 1;
	//float hydrodinamics;
	square obj;
	square player;
	square player2;
	int playerTurn = 0;
	bool playerShot;
	float playerCharge;
	float playerSwap;

};