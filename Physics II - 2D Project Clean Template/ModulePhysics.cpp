#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include "ModuleRender.h"
#include "ModuleInput.h"

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
	test.speed = 15;
	test.angle = 45;
	test.rect = {test.x, test.y, test.w,test.h};
	
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

	

	if (App->input->GetKey(SDL_SCANCODE_SPACE)) 
	{
		test.time = 0;
		test.x = 0;
		test.y = 250;
		isLaunched = true;
	
	}

	if (isLaunched == true) 
	{
		test.time += 0.1f;
		test.x += test.speed * cos(test.angle * 3.1415 / 180) * test.time;
		test.y -= test.speed * sin(test.angle * 3.1415 / 180) * test.time;
		test.y += (test.time * test.time * 10 * 0.5f);
		/*test.y += -20 + (test.speed * test.time) - (0.5f * - 9.8f * test.time * test.time);*/
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

	test.rect = { test.x, test.y, test.w,test.h };
	App->renderer->DrawQuad(test.rect,255,0,255,255);
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
