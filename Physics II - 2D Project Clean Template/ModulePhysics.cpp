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
	test.gravity = -9.8f;
	test.rect = {test.x, test.y, test.w,test.h};
	
	floor.x = 0;
	floor.y = 300;
	floor.w = 100;
	floor.h = 10;
	floor.gravity = 0;
	floor.rect = { floor.x, floor.y, floor.w,floor.h };

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	
	SDL_GetMouseState(&mousex, &mousey);

	bector = GetVector(floor.x, floor.y, mousex, mousey);

	if (App->input->GetKey(SDL_SCANCODE_SPACE)) 
	{
		test.x = 0;
		test.y = 250;

		test.force.x = mousex;
		test.force.y = mousey;
		test.time = 0;
		

		isLaunched = true;
	}


	

	/*if (!test.Intersects(floor.rect))*/
	if (isLaunched == true && test.y < 300) 
	{
		test.Gravity();

		test.xMovement();
	}
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
