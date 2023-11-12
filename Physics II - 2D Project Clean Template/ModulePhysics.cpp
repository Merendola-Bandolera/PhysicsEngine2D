#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "Fps.h"
#include "ModuleSceneIntro.h"

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

	texture = App->textures->Load("Assets/Spritesheet");

	Explosion.Pushback(0, 0, 85, 69);
	Explosion.Pushback(84, 0, 85, 69);
	Explosion.Pushback(169, 0, 85, 69);
	Explosion.Pushback(254, 0, 85, 69);
	Explosion.Pushback(339, 0, 85, 69);
	Explosion.Pushback(424, 0, 85, 69);
	Explosion.Pushback(509, 0, 85, 69);
	Explosion.Pushback(594, 0, 85, 69);
	Explosion.Pushback(679, 0, 85, 69);

	Canon.

	Ruedas.pushback(0, 201, 54, 54);
	Ruedas.pushback(53, 201, 54, 54);
	Ruedas.pushback(107, 201, 54, 54);
	Ruedas.pushback(162, 201, 54, 54);

	Canon(1, 138, 127, 36);

	test.x = 0;
	test.y = 250;
	test.w = 10;
	test.h = 10;
	
	test.speed = 1;
	test.angle = -45;
	test.rect = { test.x, test.y, test.w,test.h };
	playery = 250;
	test.vx = test.speed * cos(test.angle * 3.1415 / 180);
	test.vy = test.speed * sin(test.angle * 3.1415 / 180);

	test.ay = 10;
	test.ax = 0;
	test.acceleration = 2;

	floor.x = 0;
	floor.y = 260;
	floor.w = 1000;
	floor.h = 10;
	floor.gravity = 0;
	floor.rect = { floor.x, floor.y, floor.w,floor.h };

	tx = 0;
	ty = 250;
	tspeed = 100;
	tay = 10;
	tax = 0;

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	static char title;

	SDL_GetMouseState(&mousex, &mousey);

	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
	{
		if (limitFps == true) {
			limitFps = false;
		}
		else {
			limitFps = true;
		}
	}

	switch (SDL_KEYDOWN) {
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

	if (App->input->GetKey(SDL_SCANCODE_1)) {
		test.integrator = 1;
	}

	if (App->input->GetKey(SDL_SCANCODE_2)) {
		test.integrator = 2;
	}

	if (App->input->GetKey(SDL_SCANCODE_3)) {
		test.integrator = 3;
	}

	


	if (App->input->GetKey(SDL_SCANCODE_LEFT))
	{
		playerx--;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT))
	{
		playerx++;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) )
	{
		playery--;
	}
	else if (playery < 250) 
	{
		playery++;
	}

	if (App->input->GetKey(SDL_SCANCODE_F))
	{
		test.vx = test.speed * cos(test.angle * 3.1415 / 180);
		test.vy = test.speed * sin(test.angle * 3.1415 / 180);
		test.x = playerx;
		test.y = playery;
		test.speed = 70;

		test.time = 0;
		isLaunched = true;

	}
	
	if (isLaunched == true && test.integrator == 1)
	{
		test.time += 0.02f;
		
		
		test.x += test.vx/3 * test.time;
		test.vx += test.ax * test.time;
	
		test.y += test.vy/3 * test.time;
		test.vy += 5 * test.time * test.time;
		integratorName = "Implicit Euler";
	}
	if (isLaunched == true && test.integrator == 2)
	{
		test.time += 0.02f;
		test.vx += test.ax * test.time;
		test.x += test.vx / 3 * test.time;
		
		test.vy += 5 * test.time * test.time;
		test.y += test.vy / 3 * test.time;
	
		integratorName = "Symplectic Euler";
	}

	if (isLaunched == true && test.integrator == 3)
	{
		test.time += 0.02f;
		test.vx += test.ax * test.time;
		test.vy += test.ay * test.time;

		test.x += (test.vx) * test.time;
		test.y += (test.vy) * test.time;
		integratorName = "Velocity-Verlet";
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
	
	App->renderer->DrawQuad(cannon, 255, 255, 255, 255);
	App->renderer->DrawQuad(floor.rect, 255, 0, 0, 255);
	App->renderer->DrawLine(floor.x, 250, mousex, mousey, 100, 255, 0, 255);

	tspeed = test.speed;
	tx = 0+playerx;
	ty = playery;
	tvx = tspeed * cos(test.angle * 3.1415 / 180);
	tvy = tspeed * sin(test.angle * 3.1415 / 180);
	
	for (float i = 0; i <= 2; i+= 0.1f) {
		
		tvx += tax * i;
		tvy += tay * i;			
								
		tx += (tvx ) * i;	
		ty += (tvy ) * i;
		SDL_Rect dir = { tx, ty ,10,10 };
		App->renderer->DrawQuad(dir, 10, 100, 255, 255, 100);
	}
	App->renderer->DrawQuad(test.rect, 255, 0, 255, 255);
	char buffer[200];
	sprintf_s(buffer, "Integrator: %s ",integratorName); // Format the string

	char* myCharPointer = _strdup(buffer); // Allocate memory and copy the string

	

	App->window->SetTitle(myCharPointer);
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (!debug)
		return UPDATE_CONTINUE;

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	return true;
}
