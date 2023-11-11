#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "Fps.h"

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
	
	test.x = 0;
	test.y = 250;    
	test.w = 10;
	test.h = 10;
	test.speed = 100;
	test.angle = -45;
	test.rect = {test.x, test.y, test.w,test.h};
	playery = 250;
	test.vx = test.speed * cos(test.angle * 3.1415 / 180);
	test.vy = test.speed * sin(test.angle * 3.1415 / 180);

	test.ay = 10;
	test.ax = 0;

	floor.x = 0;
	floor.y = 260;
	floor.w = 1000;
	floor.h = 10;
	floor.gravity = 0;
	floor.rect = { floor.x, floor.y, floor.w,floor.h };

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	static char title;

	SDL_GetMouseState(&mousex, &mousey);

	switch (SDL_KEYDOWN){
		case SDL_SCANCODE_1:
			test.integrator = 1;
			break;

		case SDL_SCANCODE_2:
			test.integrator = 2;
			break;

		case SDL_SCANCODE_3:
			test.integrator = 3;
			break;

		case SDL_SCANCODE_4:
			test.integrator = 4;
			break;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) && isLaunched == false)
	{
		playerx--;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) && isLaunched == false)
	{
		playerx++;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE)) 
	{
		test.vx = test.speed * cos(test.angle * 3.1415 / 180);
		test.vy = test.speed * sin(test.angle * 3.1415 / 180);
		test.x = playerx;
		test.y = 250;

		test.time = 0;
		isLaunched = true;
	
	}

	if (isLaunched == true && test.integrator == 1)
	{
		test.x += test.speed * cos(test.angle * 3.1415 / 180) * test.time;
		test.y -= test.speed * sin(test.angle * 3.1415 / 180) * test.time;
		test.y += (test.time * test.time * 10 * 0.5f);
		test.y += -20 + (test.speed * test.time) - (0.5f * - 9.8f * test.time * test.time);
	}
	if (isLaunched == true && test.integrator == 2)
	{
		test.speed += (test.ax * sin(test.angle * 3.1415 / 180) + test.ay * cos(test.angle * 3.1415 / 180)) * test.time;
		test.x += test.speed * cos(test.angle * 3.1415 / 180) * test.time;
		test.y -= test.speed * sin(test.angle * 3.1415 / 180) * test.time;
	}

	if (isLaunched == true && test.integrator == 3)
	{
		test.time += 0.1f;
		test.vx += test.ax * test.time;
		test.vy += test.ay * test.time;

		test.x += (test.vx / 2) * test.time;
		test.y += (test.vy / 2) * test.time;
	}
	
	if (test.y >= 250) {
		isLaunched = false;
		test.y = 250;
	}
		
	
	if (App->input->GetKey(SDL_SCANCODE_A))
	{
		test.angle++;
	}

	if (App->input->GetKey(SDL_SCANCODE_D))
	{
		test.angle--;
	}
	

	/*if (!test.Intersects(floor.rect))*/
	
		return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	SDL_Rect cannon = { playerx, playery, 25,25 };
	test.rect = { test.x, test.y, test.w,test.h };
	App->renderer->DrawQuad(test.rect,255,0,255,255);
	App->renderer->DrawQuad(cannon, 255, 255, 255, 255);
	App->renderer->DrawQuad(floor.rect, 255, 0, 0, 255);
	App->renderer->DrawLine(floor.x,250,mousex,mousey,100,255,0,255);
	

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	return true;
}
