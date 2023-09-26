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
	test.rect = {test.x, test.y, test.w,test.h};
	
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	
	test.Gravity();
	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{

	test.rect = { test.x, test.y, test.w,test.h };
	App->renderer->DrawQuad(test.rect,255,0,0,255);
	

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
