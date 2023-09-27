#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include "ModuleRender.h"

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
	test.y = 0;    
	test.w = 10;
	test.h = 10;
	test.gravity = -9.8f;
	test.speed = 8;
	test.force = 8;
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
	
	if (!test.Intersects(floor.rect))
	test.Gravity();

	test.xMovement();

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{

	test.rect = { test.x, test.y, test.w,test.h };
	App->renderer->DrawQuad(test.rect,255,0,255,255);
	App->renderer->DrawQuad(floor.rect, 255, 0, 0, 255);
	

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
