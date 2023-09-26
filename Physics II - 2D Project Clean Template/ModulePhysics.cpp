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
	x = 40;
	y = 40;
	gravity = -9.81f;


	
	
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	if ( y <= 400)
	y = y - gravity;

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.h = 10;
	rect.w = 10;
	
	App->renderer->DrawQuad(rect, 23, 255, 45, 255);

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
