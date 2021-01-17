#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	CreateCircuit();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	for (int i = 0; i < primitives.Count(); i++)
	{
		primitives[i]->Update();
		primitives[i]->Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->isSensor || body2->isSensor)
	{
		if (body1 == primitives[5]->body)
		{
			App->player->ResetPosition();
		}
		else if (body1 == primitives[21]->body)
		{
			primitives[16]->wire = true;
			primitives[17]->wire = true;
			primitives[18]->wire = true;
			primitives[19]->wire = true;
		}
		else if (body1 == primitives[27]->body && balls == false)
		{
			Sphere* sphere = new Sphere(2.5);
			sphere->SetPos(230, 25, 90);
			primitives.PushBack(sphere);
			App->physics->AddBody(*sphere, 10.0f, false);
			sphere->color = { 1,0,0,1 };

			Sphere* sphere2 = new Sphere(2.5);
			sphere2->SetPos(220, 25, 90);
			primitives.PushBack(sphere2);
			App->physics->AddBody(*sphere2, 10.0f, false);
			sphere2->color = { 1,0,0,1 };

			Sphere* sphere3 = new Sphere(2.5);
			sphere3->SetPos(210, 25, 90);
			primitives.PushBack(sphere3);
			App->physics->AddBody(*sphere3, 10.0f, false);
			sphere3->color = { 1,0,0,1 };

			Sphere* sphere4 = new Sphere(2.5);
			sphere4->SetPos(200, 25, 90);
			primitives.PushBack(sphere4);
			App->physics->AddBody(*sphere4, 10.0f, false);
			sphere4->color = { 1,0,0,1 };

			Sphere* sphere5 = new Sphere(2.5);
			sphere5->SetPos(190, 25, 90);
			primitives.PushBack(sphere5);
			App->physics->AddBody(*sphere5, 10.0f, false);
			sphere5->color = { 1,0,0,1 };

			balls = true;
		}
		else if (balls == true)
		{
			if (body1 == primitives[27]->body || body1 == primitives[28]->body || body1 == primitives[29]->body)
			{
				App->player->lifes--;
			}
		}
		
		App->player->canJump = true;
	}
}

void ModuleSceneIntro::CreateCircuit()
{
	// Building scenario

	// Ground (lava)
	// 0
	Cube* ground = new Cube(1000, 1, 1000);
	ground->SetPos(0, 0, 0);
	primitives.PushBack(ground);
	App->physics->AddBody(*ground, 0.0f, false);
	ground->color = { 1,0,0,0 };

	// Ceiling (sky)
	// 1
	Cube* ceiling = new Cube(1000, 1, 1000);
	ceiling->SetPos(0, 300, 0);
	primitives.PushBack(ceiling);
	App->physics->AddBody(*ceiling, 0.0f, false);
	ceiling->color = { 0.4,0.9,1,1 };

	// Front wall (sky)
	// 2
	Cube* frontWall = new Cube(1000, 1000, 1);
	frontWall->SetPos(0, 0, 300);
	primitives.PushBack(frontWall);
	App->physics->AddBody(*frontWall, 0.0f, false);
	frontWall->color = { 0.4,0.9,1,1 };

	// Back wall (sky)
	// 3
	Cube* backWall = new Cube(1, 1000, 1000);
	backWall->SetPos(-300, 0, 0);
	primitives.PushBack(backWall);
	App->physics->AddBody(*backWall, 0.0f, false);
	backWall->color = { 0.4,0.9,1,1 };

	// Left wall (sky)
	// 4
	Cube* leftWall = new Cube(1, 1000, 1000);
	leftWall->SetPos(300, 0, 0);
	primitives.PushBack(leftWall);
	App->physics->AddBody(*leftWall, 0.0f, false);
	leftWall->color = { 0.4,0.9,1,1 };

	// Right wall (sky)
	// 5
	Cube* rightWall = new Cube(1000, 1000, 1);
	rightWall->SetPos(0, 0, -300);
	primitives.PushBack(rightWall);
	App->physics->AddBody(*rightWall, 0.0f, false);
	rightWall->color = { 0.4,0.9,1,1 };

	// Initial tunel
	// Left part
	// 6
	Cube* tunel = new Cube(1, 10, 100);
	tunel->SetPos(5, 5, 50);
	primitives.PushBack(tunel);
	App->physics->AddBody(*tunel, 0.0f, false);

	// Right part
	// 7
	Cube* tunel2 = new Cube(1, 10, 100);
	tunel2->SetPos(-5, 5, 50);
	primitives.PushBack(tunel2);
	App->physics->AddBody(*tunel2, 0.0f, false);

	// Ramp up
	// 8
	Cube* rampUp = new Cube(10, 100, 1);
	rampUp->SetPos(0, 1, 30);
	rampUp->SetRotation(75, { 1,0,0 });
	primitives.PushBack(rampUp);
	rampUp->color = { 0.25,0.25,0.25,1 };
	App->physics->AddBody(*rampUp, 0.0f, false);

	// Ramp down
	// 9
	Cube* rampDown = new Cube(10, 30, 1);
	rampDown->SetPos(0, 10, 130);
	rampDown->SetRotation(285, { 1,0,0 });
	primitives.PushBack(rampDown);
	rampDown->color = { 0.25,0.25,0.25 };
	App->physics->AddBody(*rampDown, 0.0f, false);

	// Ramp jump
	// 10
	Cube* rampJump = new Cube(10, 5, 1);
	rampJump->SetPos(0, 8, 140);
	rampJump->SetRotation(75, { 1,0,0 });
	primitives.PushBack(rampJump);
	rampJump->color = { 0.25,0.25,0.25 };
	App->physics->AddBody(*rampJump, 0.0f, false);

	// Cube to stop the car (Checkpoint)
	// Base
	// 11
	Cube* stopBase = new Cube(60, 1, 15);
	stopBase->SetPos(22.5, 5, 175);
	primitives.PushBack(stopBase);
	App->physics->AddBody(*stopBase, 0.0f, false);

	// Wall
	// 12
	Cube* stopWall = new Cube(15, 15, 1);
	stopWall->SetPos(0, 12.5, 182.5);
	primitives.PushBack(stopWall);
	App->physics->AddBody(*stopWall, 0.0f, false);

	//Fence
	// 13
	Cube* stopFence = new Cube(15, 2, 1);
	stopFence->SetPos(0, 6, 167.5);
	primitives.PushBack(stopFence);
	App->physics->AddBody(*stopFence, 0.0f, false);

	// Platforms to jump on
	// 14
	Cube* platform = new Cube(30, 1, 15);
	platform->SetPos(97.5, 10, 175);
	primitives.PushBack(platform);
	App->physics->AddBody(*platform, 0.0f, false);

	// 15
	Cube* platform2 = new Cube(45, 1, 15);
	platform2->SetPos(157.5, 12.5, 175);
	primitives.PushBack(platform2);
	App->physics->AddBody(*platform2, 0.0f, false);

	// Tube
	// 16
	Cube* tube = new Cube(15, 10, 1);
	tube->SetPos(210, 13.25, 167.5);
	primitives.PushBack(tube);
	App->physics->AddBody(*tube, 0.0f, false);

	// 17
	Cube* tube2 = new Cube(15, 15, 1);
	tube2->SetPos(210, 10.75, 182.5);
	primitives.PushBack(tube2);
	App->physics->AddBody(*tube2, 0.0f, false);

	// 18
	Cube* tube3 = new Cube(1, 15, 15);
	tube3->SetPos(202.5, 10.75, 175);
	primitives.PushBack(tube3);
	App->physics->AddBody(*tube3, 0.0f, false);

	// 19
	Cube* tube4 = new Cube(1, 30, 15);
	tube4->SetPos(217.5, 18.25, 175);
	primitives.PushBack(tube4);
	App->physics->AddBody(*tube4, 0.0f, false);

	// 20
	// Under tube platform
	Cube* tubePlatform = new Cube(15, 1, 15);
	tubePlatform->SetPos(210, 1, 175);
	primitives.PushBack(tubePlatform);
	App->physics->AddBody(*tubePlatform, 0.0f, false);

	// 21
	// Tube sensor
	Cube* tubeSensor = new Cube(15, 1, 15);
	tubeSensor->SetPos(210, 5, 175);
	tubeSensor->wire = true;
	primitives.PushBack(tubeSensor);
	App->physics->AddBody(*tubeSensor, 0.0f, true, this);

	// 22
	// Bounds
	Cube* platform11 = new Cube(15, 2, 1);
	platform11->SetPos(210, 1, 182.5);
	primitives.PushBack(platform11);
	App->physics->AddBody(*platform11, 0.0f, false);

	// 23
	Cube* platform12 = new Cube(1, 2, 15);
	platform12->SetPos(202.5, 1, 175);
	primitives.PushBack(platform12);
	App->physics->AddBody(*platform12, 0.0f, false);

	// 24
	Cube* platform13 = new Cube(1, 2, 15);
	platform13->SetPos(217.5, 1, 175);
	primitives.PushBack(platform13);
	App->physics->AddBody(*platform13, 0.0f, false);

	// 25
	Cube* platform14 = new Cube(15, 1, 15);
	platform14->SetPos(210, 3, 161);
	platform14->SetRotation(15, { 1,0,0 });
	primitives.PushBack(platform14);
	App->physics->AddBody(*platform14, 0.0f, false);

	// 26
	Cube* platform15 = new Cube(60, 1, 60);
	platform15->SetPos(210, 10, 115);
	platform15->SetRotation(15, { 1,0,0 });
	primitives.PushBack(platform15);
	App->physics->AddBody(*platform15, 0.0f, false);

	//27
	// Balls sensor (at jump)
	Cube* platform16 = new Cube(15, 15, 1);
	platform16->SetPos(210, 5, 155);
	platform16->wire = true;
	/*platform16->color = { 1,0,0 };*/
	primitives.PushBack(platform16);
	App->physics->AddBody(*platform16, 0.0f, true, this);

	// Balls for constraints links
	//28
	Sphere* sphere = new Sphere(1);
	sphere->SetPos(0, 25, 90);
	primitives.PushBack(sphere);
	App->physics->AddBody(*sphere, 0.0f, false);

	//29
	Sphere* sphere2 = new Sphere(2.5);
	sphere2->SetPos(0, 20, 90);
	primitives.PushBack(sphere2);
	App->physics->AddBody(*sphere2, 100.0f, false);
	sphere2->body->Push(1000.0f, 0.0f, 0.0f);

	App->physics->AddConstraintP2P(*sphere->body, *sphere2->body, vec3{ 0, 0, 0 }, vec3{ sphere->transform.translation().x - sphere2->transform.translation().x, sphere->transform.translation().y - sphere2->transform.translation().y, sphere->transform.translation().z - sphere2->transform.translation().z });

	// Reset / Checkpoint
	/*Cube* finishLine = new Cube(30, 20, 5);
	finishLine->SetPos(0, 10, 180);
	primitives.PushBack(finishLine);
	App->physics->AddBody(*finishLine, 0.0f, true, this);
	finishLine->color = { 0.0,1.0,0.0,1.0 };*/
}