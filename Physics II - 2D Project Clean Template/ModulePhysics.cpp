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

	texture = App->textures->Load("../Assets/Spritesheet.png");
	texture2 = App->textures->Load("../Assets/fondo.png");
	texture3 = App->textures->Load("../Assets/bomba.png");

	Explosion.PushBack({0, 0, 85, 69});
	Explosion.PushBack({84, 0, 85, 69});
	Explosion.PushBack({169, 0, 85, 69});
	Explosion.PushBack({254, 0, 85, 69});
	Explosion.PushBack({339, 0, 85, 69});
	Explosion.PushBack({424, 0, 85, 69});
	Explosion.PushBack({509, 0, 85, 69});
	Explosion.PushBack({594, 0, 85, 69});
	Explosion.PushBack({ 679, 0, 85, 69 });

	

	Ruedas.PushBack({0, 201, 54, 54});
	Ruedas.PushBack({53, 201, 54, 54});
	Ruedas.PushBack({107, 201, 54, 54});
	Ruedas.PushBack({ 162, 201, 54, 54 });

	Canon.PushBack({ 1, 138, 127, 36 });

	obj.x = 0;
	obj.y = 588;
	obj.w = 30;
	obj.h = 25;
	
	obj.speed = 1;
	obj.angle = -45;
	obj.rect = { obj.x, obj.y, obj.w,obj.h };
	playery = 588;
	obj.vx = obj.speed * cos(obj.angle * 3.1415 / 180);
	obj.vy = obj.speed * sin(obj.angle * 3.1415 / 180);

	obj.ay = 10;
	obj.ax = 0;
	obj.acceleration = 2;
	obj.mass = 7.5f;
	obj.roce = 2;

	floor.x = 150;
	floor.y = 588;
	floor.w = 100;
	floor.h = 1000;
	
	floor.rect = { floor.x, floor.y, floor.w,floor.h };

	tx = 0;
	ty = 588;
	tspeed = 100;
	tay = 10;
	tax = 0;

	

	return true;
}


update_status ModulePhysics::PreUpdate()
{
	static char title;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;



	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();

	dt = (double)((NOW - LAST) * 1000 / SDL_GetPerformanceFrequency());
	deltaTime = (float)dt;

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


	if (App->input->GetKey(SDL_SCANCODE_1)) {
		obj.integrator = 1;
	}

	if (App->input->GetKey(SDL_SCANCODE_2)) {
		obj.integrator = 2;
	}

	if (App->input->GetKey(SDL_SCANCODE_3)) {
		obj.integrator = 3;
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
	else if (playery < 588)
	{
		playery++;
	}

	if (App->input->GetKey(SDL_SCANCODE_F))
	{
		obj.vx = obj.speed * cos(obj.angle * 3.1415 / 180);
		obj.vy = obj.speed * sin(obj.angle * 3.1415 / 180);
		obj.x = playerx+120;
		obj.y = playery-70;
		obj.speed = 70;
		obj.ay = 0;
		obj.ax = 0;
		obj.time = 0;
		isLaunched = true;

	}
	
	//INTEGRATOR 1
	if (isLaunched == true && obj.integrator == 1)
	{		
		ForceSum(obj, 50, 50);
		SymplecticEuler(obj);
	}
	//INTEGRATOR 2
	if (isLaunched == true && obj.integrator == 2)
	{
		ForceSum(obj, 50, 50);
		ImplicitEuler(obj);	
	}	
	//INTEGRATOR 3
	if (isLaunched == true && obj.integrator == 3)
	{
		ForceSum(obj, 50, 50);
		VelocityVerlet(obj);		
	}

	/*if (obj.y >= 588 && isSwamp == false && obj.x < 150 && obj.x > 250) {
		isLaunched = false;
		obj.vy = 0;
		obj.y = 588;
	}*/

	//CONTROLES
	if (App->input->GetKey(SDL_SCANCODE_D))
	{
		obj.angle++;
	}

	if (App->input->GetKey(SDL_SCANCODE_A))
	{
		obj.angle--;
	}

	//if (test.vy <0.1f && test.vy > -0.1f) {
	//	yMax = test.y;
	//}

	//HYDRODINAMICS
	if (obj.x > 150 && obj.x < 250 && obj.y >= 588)
		isSwamp = true;
	else {
		isSwamp = false;
	}
	/*if (App->input->GetKey(SDL_SCANCODE_4)) {
		isSwamp = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_5)) {
		isSwamp = false;
	}*/
	//	//FUERZA BOYANCI
	//	test.buoyancy += (0.3f * 9.8f * 1.75f) ;

	//	//FUERZA GRAVEDAD
	//	//test.gravity += test.mass * 9.8f ;

	///*	test.vy += -test.buoyancy;*/
	//	
	//	//ROZAMIENTO
	//	if (test.vy < 0) {
	//	test.roce += 10 *test.vy ;
	//	}
	//	else if (test.vy >= 0) {
	//	test.roce -= 10*test.vy;
	//	}

	//	//FUERZA TOTAL = FG + BOUYANCY -ROCE
	//	//(test.force.y += test.gravity - test.buoyancy + test.roce;

	//	//VELOCIDAD = (Ft/MASA)*TIEMPO
	//	//test.vy -= (test.force.y / test.mass) * (test.time);

	//	isLaunched = true;
	//
	//	
	//			
	//}
	//else {
	//	isSwamp = false;
	//	
	//	test.buoyancy = 0; 
	//	//ROZAMIENTO
	//	if (test.vy < 0) {
	//		test.roce -= 0.1f * test.vy;
	//	}
	//	else if (test.vy >= 0) {
	//		test.roce += 0.1f * test.vy;
	//	}


	//	test.vy += test.ay * test.time;
	//	test.y += (test.vy) * test.time;
	//	
	//}

	//


	/*if (!test.Intersects(floor.rect))*/

	return UPDATE_CONTINUE;
}

bool ModulePhysics::Collide(SDL_Rect& r, SDL_Rect& r2)
{
	return (r2.x < r.x + r.w &&
		r2.x + r2.w > r.x &&
		r2.y < r.y + r.h &&
		r2.h + r2.y > r.y);
}

void ModulePhysics::ForceSum(square &obj, float launchforcex, float launchforcey)
{
	float gforce;

	float aerodynamics;

	if (Collide(obj.rect, floor.rect))
	{
		isSwamp = true;
	}
	else if (!Collide(obj.rect, floor.rect)) {
		isSwamp = false;
	}

	if (Collide(obj.rect, suelo)) {
		CollisionResolution(obj, suelo);
	}
	if (Collide(obj.rect, suelo2)) {
		CollisionResolution(obj, suelo2);
	}

	launchforcex = 10 * cos(obj.angle * 3.1415 / 180);
	launchforcey = 10 * sin(obj.angle * 3.1415 / 180);


	obj.TotalForce.x = launchforcex;
	obj.TotalForce.y = launchforcey;

	gforce = obj.mass * 9.8f ; //masa * gravedad

	if (isSwamp == true) {
		
		obj.TotalForce.x = 0;
		obj.vx *= 0.9;
		obj.vy *= 0.9;
		aerodynamics = 0;

		obj.roce = obj.vy* 0.1f; //drag del awa

		//hydrodinamics += (0.3f * 9.8 * 1.75f) + obj.roce * obj.vy; // Densidad agua * Gravedad * Volumen
		hydrodinamics += 9.8f * obj.surface * obj.vy;
		hydrodinamics += obj.roce * obj.vy;
	}
	

	if (isSwamp == false)
	{
		
		hydrodinamics = -hydrodinamics - gforce;
		aerodynamics = 1 / 2 * obj.density * obj.vy * obj.vy *obj.surface * obj.CDrag; //0.5 * densidad * v*v * Surface * coeficiente 
	}

	

	obj.TotalForce.x += - aerodynamics;
	obj.TotalForce.y += gforce - hydrodinamics - aerodynamics ;
	if (isSwamp == false)
	{
		hydrodinamics = 0;
	}


}

void ModulePhysics::CollisionResolution(square &obj, SDL_Rect &r) {
	Vector2D objpos;
	Vector2D rpos;
	Vector2D diff;
	objpos.x = obj.x;
	objpos.y = obj.y;

	rpos.x = r.x;
	rpos.y = r.y;

	diff.x	= rpos.x - objpos.x;
	diff.y = rpos.y - objpos.y;
	int colWidth, colHeight;

	// Calculate collision box
	if (diff.x > 0) {
		colWidth = obj.rect.w - diff.x;
	}
	else {
		colWidth = r.w + diff.x;
	}

	if (diff.y > 0) {
		colHeight = obj.rect.h - diff.y;
	}
	else {
		colHeight = r.h + diff.y;
	}

	// Reposition object
	if (colWidth < colHeight) {
		// Reposition by X-axis
		if (diff.x > 0) {
			obj.x -= colWidth;
		}
		else {
			obj.x += colWidth;
		}

		obj.vx = -obj.vx * 0.5f;
	}
	else {
		// Reposition by Y-axis
		if (diff.y > 0) {
			obj.y -= colHeight;
		}
		else {
			obj.y += colHeight-5;
		}

		obj.vy = -obj.vy * 0.7f;
		obj.vx *= 0.5f;
	}

}

void ModulePhysics::VelocityVerlet(square &obj) {
	
	obj.ax = obj.TotalForce.x / obj.mass;

	obj.ay = obj.TotalForce.y / obj.mass;

	obj.x += (obj.vx) * 0.125f + 0.5 * obj.ax * 0.125f * 0.125f;
	obj.y += (obj.vy) * 0.125f + 0.5 * obj.ay * 0.125f * 0.125f;

	obj.vx += obj.ax * 0.125f;
	obj.vy += obj.ay * 0.125f;

	integratorName = "Velocity-Verlet";
}
void ModulePhysics::ImplicitEuler(square &obj) {

	obj.ax = obj.TotalForce.x / obj.mass;

	obj.ay = obj.TotalForce.y / obj.mass;



	obj.x += obj.vx  * 0.125f;
	obj.vx += obj.ax * 0.125f;

	obj.y += obj.vy * 0.125f;
	obj.vy += obj.ay * 0.125f;
	integratorName = "Implicit Euler";
}
void ModulePhysics::SymplecticEuler(square &obj) {

	obj.ax = obj.TotalForce.x / obj.mass;

	obj.ay = obj.TotalForce.y / obj.mass;


	obj.vx += obj.ax * 0.125f;
	obj.x += obj.vx* 0.125f;

	obj.vy += obj.ay * 0.125f;
	obj.y += obj.vy * 0.125f;

	integratorName = "Symplectic Euler";
}
// 
update_status ModulePhysics::PostUpdate()
{
	
	SDL_Rect cannon = { 1, 138, 127, 36 };
	SDL_Rect rueda = { 0, 201, 54, 54 };
	
	obj.rect = { obj.x, obj.y-25, obj.w,obj.h };
	App->renderer->Blit(texture2, 0, 0);
	//App->renderer->DrawQuad(cannon, 255, 255, 255, 255);
	App->renderer->Blit(texture, playerx, playery -75,&cannon);
	App->renderer->Blit(texture, playerx, playery - 50, &rueda);
	
	App->renderer->DrawQuad(suelo, 0, 255, 0, 255);
	App->renderer->DrawQuad(suelo2, 0, 255, 0, 255);
	App->renderer->DrawQuad(floor.rect, 0, 0, 255, 255);
	App->renderer->DrawQuad(obj.rect, 255, 0, 0, 255);
	//App->renderer->DrawLine(floor.x, 588, mousex, mousey, 100, 255, 0, 255);

	tspeed = obj.speed;
	tx = 0+playerx +120;
	ty = playery -70;
	tvx = tspeed * cos(obj.angle * 3.1415 / 180);
	tvy = tspeed * sin(obj.angle * 3.1415 / 180);

	
	
	for (float i = 0; i <= 0.6; i+= 0.1f) {
		
		tvx += tax * i;
		tvy += tay * i;			
								
		tx += (tvx ) * i;	
		ty += (tvy ) * i;
		SDL_Rect dir = { tx, ty ,10,10 };
		App->renderer->DrawQuad(dir, 10, 100, 255, 255, 100);
	}


	//App->renderer->DrawQuad(test.rect, 255, 0, 255, 255);
	App->renderer->Blit(texture3, obj.x-70, obj.y-90);
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
