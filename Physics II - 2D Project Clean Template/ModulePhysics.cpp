#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "Fps.h"
#include "ModuleSceneIntro.h"

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = false;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	texture = App->textures->Load("../Assets/Spritesheet.png");
	texture2 = App->textures->Load("../Assets/fondowater.png");
	texture3 = App->textures->Load("../Assets/corcho.png");
	texture4 = App->textures->Load("../Assets/player1.png");
	texture5 = App->textures->Load("../Assets/player2 (1).png");
	texture6 = App->textures->Load("../Assets/short platform.png");
	texture7 = App->textures->Load("../Assets/long platform.png");
	texture8 = App->textures->Load("../Assets/vertical platform.png");
	texture9 = App->textures->Load("../Assets/player1win.png");
	texture10 = App->textures->Load("../Assets/player2win.png");

	

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
	obj.mass = 20.5f;
	obj.roce = 2;
	obj.name = 'c';

	player.x = 0;
	player.y = 250;
	player.w = 130;
	player.h = 25;
	player.name = 'p';
	
	player.speed = 1;
	player.angle = -45;
	player.rect = { player.x, player.y, player.w,player.h };
	
	player.vx = player.speed * cos(player.angle * 3.1415 / 180);
	player.vy = player.speed * sin(player.angle * 3.1415 / 180);
	
	player.ay = 10;
	player.ax = 0;
	player.acceleration = 2;
	player.mass = 7.5f;
	player.roce = 2;

	player2.x = 850;
	player2.y = 350;
	player2.w = 130;
	player2.h = 25;
	player2.name = 'p';

	player2.speed = 1;
	player2.angle = -45;
	player2.rect = { player.x, player.y, player.w,player.h };

	player2.vx = player.speed * cos(player.angle * 3.1415 / 180);
	player2.vy = player.speed * sin(player.angle * 3.1415 / 180);

	player2.ay = 10;
	player2.ax = 0;
	player2.acceleration = 2;
	player2.mass = 7.5f;
	player2.roce = 2;

	floor.x = 0;
	floor.y = 588;
	floor.w = 1100;
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

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		if (gravity == true) {
			gravity = false;
		}
		else {
			gravity = true;
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

	
	if (!App->input->GetKey(SDL_SCANCODE_LEFT) && !App->input->GetKey(SDL_SCANCODE_LEFT) && playerTurn == 0) {
		player.ax = 0;

	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) && playerTurn == 0 && player.fuel > 0)
	{
		//playerx--;
		player.x--;
		player.fuel -= 0.5f;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) && playerTurn == 0 && player.x <= 900 && player.fuel > 0)
	{
		//playerx++;
		player.x++;
		player.fuel -= 0.5f;
	}

	player.jumpcd++;
	player.jumping = false;
	player2.jumpcd++;
	player2.jumping = false;

	if (App->input->GetKey(SDL_SCANCODE_SPACE) && player.vy == 0 && playerTurn == 0 || App->input->GetKey(SDL_SCANCODE_SPACE) && player.isSwamp == true && playerTurn == 0 && player.jumpcd > 30)
	{
		//playery--;
        player.ay = 0;
		player.vy = -130;
		player.y -= 0;
		player.jumping = true;
		player.jumpcd = 0;
		
	}

	if (!App->input->GetKey(SDL_SCANCODE_LEFT) && !App->input->GetKey(SDL_SCANCODE_LEFT) && playerTurn == 1) {
		player2.ax = 0;

	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) && playerTurn == 1 && player2.fuel > 0)
	{
		//playerx--;
		player2.x--;
		player2.fuel -= 0.5f;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) && playerTurn == 1 && player2.x <= 900 && player2.fuel > 0)
	{
		//playerx++;
		player2.x++;
		player2.fuel -= 0.5f;
	}

	

	if (App->input->GetKey(SDL_SCANCODE_SPACE) && player2.vy == 0 && playerTurn == 1 || App->input->GetKey(SDL_SCANCODE_SPACE) && player2.isSwamp == true && playerTurn == 1 && player2.jumpcd >30)
	{
		//playery--;
		player2.ay = 0;
		player2.vy = -130;
		player2.y -= 0;
		player2.jumping = true;
		player2.jumpcd = 0;
			  
		player2.jumping = true;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_F) && playerShot == false)
	{
		playerCharge = 0;
		playerSwap = 0;
		playerShot = true;
		App->audio->PlayFx(App->audio->LoadFx("../Assets/bottle1.wav"), 0);
	}
	
	if (playerShot == true ) {
		playerCharge++;
		playerSwap++;
	}
	if (playerCharge <= 20 && playerTurn == 0) {
		float agnulo = obj.angle;
		obj.vx = obj.speed * cos(agnulo * 3.1415 / 180);
		obj.vy = obj.speed * sin(agnulo * 3.1415 / 180);
		obj.vx *= force;
		obj.vy *= force;
		obj.x = player.x + 120;
		obj.y = player.y - 70 + 25;
		obj.speed = 70;
		obj.ay = 0;
		obj.ax = 0;
		obj.time = 0;
		isLaunched = true;

	}

	if (playerSwap >= 200 && playerTurn == 0) {
		playerShot = false;
		playerTurn = 1;
		playerSwap = 0;
		player.fuel = 100;
	}


	if (playerCharge <= 20 && playerTurn == 1) {
		float agnulo = obj.angle;
		obj.vx = obj.speed * cos(agnulo * 3.1415 / 180);
		obj.vy = obj.speed * sin(agnulo * 3.1415 / 180);
		obj.vx *= force;
		obj.vy *= force;
		obj.x = player2.x;
		obj.y = player2.y - 70 + 25;
		obj.speed = 70;
		obj.ay = 0;
		obj.ax = 0;
		obj.time = 0;
		isLaunched = true;
		playerShot = true;
		
	}

	if (playerSwap >= 200 && playerTurn == 1) {
		playerShot = false;
		playerTurn = 0;
		playerSwap = 0;
		player2.fuel = 100;
	}


	//if (obj.vy == 0 && obj.vx == 0 && playerTurn == 0) {
	//	playerTurn = 1;
	//}

	//if (obj.vy == 0 && obj.vx == 0 && playerTurn == 1) {
	//	playerTurn = 0;
	//}
	//INTEGRATOR 1
	if (isLaunched == true && obj.integrator == 1)
	{		
		ForceSum(obj, 10, 100);
		SymplecticEuler(obj);
	}
	//INTEGRATOR 2
	if (isLaunched == true && obj.integrator == 2)
	{
		ForceSum(obj, 10, 100);
		ImplicitEuler(obj);	
	}	
	//INTEGRATOR 3
	if (isLaunched == true && obj.integrator == 3)
	{
		ForceSum(obj, 10, 100);
		VelocityVerlet(obj);		
	}

	if (player.jumping == false)
	ForceSum(player, 0, 0);
		

	VelocityVerlet(player);

	if (player2 .jumping == false)
	ForceSum(player2, 0, 0);

	VelocityVerlet(player2);

	if (Collide(obj.rect, player.rect)) 
	{
		obj.ax = 0;
		obj.ay = 0;
		obj.vy = 0;
		obj.vx = 0;
		obj.x = 1400;
		obj.y = 400;
		player.hp -= 1;
	}
	if (Collide(obj.rect, player2.rect )) {
		obj.ax = 0;
		obj.ay = 0;
		obj.vy = 0;
		obj.vx = 0;
		obj.x = 1400;
		obj.y = 400;
		player2.hp -= 1;
	}


	//CONTROLES
	if (App->input->GetKey(SDL_SCANCODE_D))
	{
		obj.angle++;
	}

	if (App->input->GetKey(SDL_SCANCODE_A))
	{
		obj.angle--;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) && force <= 1.5f)
	{
		force+= 0.025f;
	}

	if (App->input->GetKey(SDL_SCANCODE_S)&& force >= 0)
	{
		force-= 0.025f;
	}

	

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
		obj.isSwamp = true;
	}
	else if (!Collide(obj.rect, floor.rect)) {
		obj.isSwamp = false;
	}
	if (Collide(obj.rect, wall)) {
		CollisionResolution(obj, wall);
	}
	if (Collide(obj.rect, wall3)) {
		CollisionResolution(obj, wall3);
	}
	if (Collide(obj.rect, wall4)) {
		CollisionResolution(obj, wall4);
	}
	if (Collide(obj.rect, wall5)) {
		CollisionResolution(obj, wall5);
	}
	if (Collide(obj.rect, wall6)) {
		CollisionResolution(obj, wall6);
	}
	if (Collide(obj.rect, wall7)) {
		CollisionResolution(obj, wall7);
	}
	if (Collide(obj.rect, wall8)) {
		CollisionResolution(obj, wall8);
	}
	if (Collide(obj.rect, wall9)) {
		CollisionResolution(obj, wall9);
	}
	if (Collide(obj.rect, suelo) && obj.name != 'p') {
		CollisionResolution(obj, suelo);
	}
	if (Collide(obj.rect, suelo2) && obj.name != 'p') {
		CollisionResolution(obj, suelo2);
	}
	if (Collide(obj.rect, suelo3) && obj.name != 'p') {
		CollisionResolution(obj, suelo3);
	}
	/*if (Collide(obj.rect, suelo3) && obj.name != 'p') {
		CollisionResolution(obj, suelo3);
	}
	if (Collide(obj.rect, suelo4) && obj.name != 'p') {
		CollisionResolution(obj, suelo4);
	}*/
	


	obj.TotalForce.x = launchforcex;
	obj.TotalForce.y = launchforcey;

	gforce = obj.mass * 9.8f ; //masa * gravedad

	if (obj.isSwamp == true && gravity == false) {
		
		obj.TotalForce.x = 0;
		obj.vx *= 0.94;
		obj.vy *= 0.92;
		aerodynamics = 0;

		obj.roce = /*obj.vy**/ 0.8f; //drag del awa

		//hydrodinamics += (0.3f * 9.8 * 1.75f) + obj.roce * obj.vy; // Densidad agua * Gravedad * Volumen
		obj.hydrodinamics += 9.8f * obj.surface * obj.vy;
		obj.hydrodinamics += obj.roce * obj.vy;
	}
	

	if (obj.isSwamp == false)
	{
		
		obj.hydrodinamics = -obj.hydrodinamics - gforce;
		aerodynamics = 1 / 2 * obj.density * obj.vy * obj.vy *obj.surface * obj.CDrag; //0.5 * densidad * v*v * Surface * coeficiente 
	}

	
		if (gravity == false)
	obj.TotalForce.x += - aerodynamics;
	obj.TotalForce.y += gforce - obj.hydrodinamics ;

	if (gravity) {
		obj.TotalForce.y = 0;
		
	}

	if (Collide(obj.rect, suelo) && obj.name == 'p' && obj.y != 0) {
		obj.TotalForce.y = 0;
		obj.vy = 0;
		obj.ay = 0;
	}
	if (Collide(obj.rect, suelo2) && obj.name == 'p' && obj.y != 0) {
		obj.TotalForce.y = 0;
		obj.vy = 0;
		obj.ay = 0;
	}
	if (Collide(obj.rect, suelo3) && obj.name == 'p' && obj.y != 0) {
		obj.TotalForce.y = 0;
		obj.vy = 0;
		obj.ay = 0;
	}

	if (obj.isSwamp == false)
	{
		obj.hydrodinamics = 0;
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

		if (obj.name != 'p')
		obj.vx = -obj.vx * 0.5f;
	}
	else {
		// Reposition by Y-axis
		if (obj.name != 'p') {
			if (diff.y > 0) {
				obj.y -= colHeight;
			}
			else {
				obj.y += colHeight - 5;
			}
		}
		else {
			if (diff.y > 0) {
				obj.y -= colHeight;
			}
			else {
				obj.y += colHeight;
			}
			obj.vy = 0;
			obj.ay = 0;
			obj.TotalForce.y = 0;
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
	if (obj.name != 'p')
	integratorName = "Velocity-Verlet";
}
void ModulePhysics::ImplicitEuler(square &obj) {

	obj.ax = obj.TotalForce.x / obj.mass;

	obj.ay = obj.TotalForce.y / obj.mass;



	obj.x += obj.vx  * 0.125f;
	obj.vx += obj.ax * 0.125f;

	obj.y += obj.vy * 0.125f;
	obj.vy += obj.ay * 0.125f;
	if (obj.name != 'p')
	integratorName = "Implicit Euler";
}
void ModulePhysics::SymplecticEuler(square &obj) {

	obj.ax = obj.TotalForce.x / obj.mass;

	obj.ay = obj.TotalForce.y / obj.mass;


	obj.vx += obj.ax * 0.125f;
	obj.x += obj.vx* 0.125f;

	obj.vy += obj.ay * 0.125f;
	obj.y += obj.vy * 0.125f;
	if (obj.name != 'p')
	integratorName = "Symplectic Euler";
}

update_status ModulePhysics::PostUpdate()
{
	
	SDL_Rect cannon = { 1, 138, 127, 36 };
	SDL_Rect rueda = { 0, 201, 54, 54 };
	
	obj.rect = { obj.x, obj.y-25, obj.w,obj.h };
	player.rect = { player.x, player.y, player.w,player.h };
	player2.rect = { player2.x, player2.y, player2.w,player2.h };

	App->renderer->Blit(texture2, 0, 0);
	//App->renderer->DrawQuad(player.rect, 0, 255, 255, 255);
	//App->renderer->DrawQuad(cannon, 255, 255, 255, 255);
	App->renderer->Blit(texture4, player.x, player.y -75);
	App->renderer->Blit(texture, player.x, player.y - 25, &rueda);
	App->renderer->Blit(texture, player.x +76, player.y - 25, &rueda);
	App->renderer->Blit(texture5, player2.x, player2.y - 75);
	App->renderer->Blit(texture, player2.x + 76, player2.y - 25, &rueda);
	App->renderer->Blit(texture, player2.x, player2.y - 25, &rueda);


	App->renderer->Blit(texture8, wall.x, wall.y);
	App->renderer->Blit(texture8, wall.x, wall.y+wall.h/2+7);
	App->renderer->Blit(texture8, wall.x, wall.y + wall.h + 14);

	App->renderer->Blit(texture8, wall4.x-20, wall4.y + wall4.h/2 + 30);
	App->renderer->Blit(texture8, wall4.x-20, wall4.y + wall4.h + 30);
	App->renderer->Blit(texture8, wall4.x-20, wall4.y);

	App->renderer->Blit(texture8, wall6.x - 20, wall6.y + wall6.h / 2 + 30);
	App->renderer->Blit(texture8, wall6.x - 20, wall6.y + wall6.h + 30);
	App->renderer->Blit(texture8, wall6.x - 20, wall6.y);

	App->renderer->Blit(texture8, wall8.x, wall8.y + wall8.h / 2 + 30);
	App->renderer->Blit(texture8, wall8.x, wall8.y + wall8.h + 30);
	App->renderer->Blit(texture8, wall8.x, wall8.y);


	App->renderer->Blit(texture6,suelo.x,suelo.y, 0, 255, 0, 255);
	App->renderer->Blit(texture7, suelo2.x, suelo2.y, 0, 255, 0, 255);
	App->renderer->Blit(texture7, suelo3.x, suelo3.y, 0, 255, 0, 255);

	if (debug) {

	
	App->renderer->DrawQuad(suelo, 0, 255, 0, 255);
	App->renderer->DrawQuad(suelo2, 0, 255, 0, 255);
	App->renderer->DrawQuad(suelo3, 0, 255, 0, 255);
	App->renderer->DrawQuad(wall, 255, 255, 0, 255);
	App->renderer->DrawQuad(wall3, 255, 255, 0, 255);

	App->renderer->DrawQuad(wall5, 255, 255, 0, 255);
	App->renderer->DrawQuad(wall4, 255, 255, 0, 255);

	App->renderer->DrawQuad(wall6, 255, 255, 0, 255);
	App->renderer->DrawQuad(wall7, 255, 255, 0, 255);

	App->renderer->DrawQuad(wall8, 255, 255, 0, 255);
	App->renderer->DrawQuad(wall9, 255, 255, 0, 255);
	App->renderer->DrawQuad(floor.rect, 0, 0, 255, 255);
	App->renderer->DrawQuad(obj.rect, 255, 0, 0, 255);
	}
	
	//App->renderer->DrawLine(floor.x, 588, mousex, mousey, 100, 255, 0, 255);


	if (playerTurn == 0) {
		tspeed = obj.speed;
		tx = 0 + player.x + 120;
		ty = player.y - 70 + 25;
		tvx = tspeed * cos(obj.angle * 3.1415 / 180);
		tvy = tspeed * sin(obj.angle * 3.1415 / 180);
	}

	if (playerTurn == 1) {
		tspeed = obj.speed;
		tx = 0 + player2.x ;
		ty = player2.y - 70 + 25;
		tvx = tspeed * cos(obj.angle * 3.1415 / 180);
		tvy = tspeed * sin(obj.angle * 3.1415 / 180);
	}

	
	
	for (float i = 0; i <= 0.6; i+= 0.1f) {
		
		tvx += tax * i;
		tvy += tay * i;			
								
		tx += (tvx ) * i;	
		ty += (tvy ) * i;
		SDL_Rect dir = { tx, ty ,10,10 };
		App->renderer->DrawQuad(dir, 10, 100, 255, 255, 100);
	}


	if (player.hp <= 0) {
		App->renderer->Blit(texture10, 0, 0);
	}
	if (player2.hp <= 0) {
		App->renderer->Blit(texture9, 0, 0);
	}

	//App->renderer->DrawQuad(test.rect, 255, 0, 255, 255);
	App->renderer->Blit(texture3, obj.x, obj.y-32);
	char buffer[200];
	sprintf_s(buffer, "Player1: HP %d Fuel %.1f      Player2: HP %d Fuel %.1f,           Integrator: %s , Locked FPS: %d, PlayerTurn: %d, ShotForce: %.1f, ShotAngle: %.1f", player.hp, player.fuel, player2.hp, player2.fuel,integratorName,limitFps,playerTurn,force,obj.angle); // Format the string

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
