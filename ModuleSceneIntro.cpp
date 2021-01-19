#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	spawnedBalls1 = false;
	spawnedBalls2 = false;
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
	if (body1->type == ElementType::TUBE_SENSOR && body1->isSensor)
	{
		primitives[16]->wire = true;
		primitives[17]->wire = true;
		primitives[18]->wire = true;
		primitives[19]->wire = true;
	}
	else if (body1->type == ElementType::SPAWN_SENSOR && body1->isSensor && spawnedBalls1 == false)
	{
		Sphere* sphere = new Sphere(2.5);
		sphere->SetPos(230, 25, 90);
		primitives.PushBack(sphere);
		App->physics->AddBody(*sphere, 10.0f, ElementType::DAMAGE);
		sphere->color = { 1,0,0,1 };

		Sphere* sphere2 = new Sphere(2.5);
		sphere2->SetPos(220, 25, 90);
		primitives.PushBack(sphere2);
		App->physics->AddBody(*sphere2, 10.0f, ElementType::DAMAGE);
		sphere2->color = { 1,0,0,1 };

		Sphere* sphere3 = new Sphere(2.5);
		sphere3->SetPos(210, 25, 90);
		primitives.PushBack(sphere3);
		App->physics->AddBody(*sphere3, 10.0f, ElementType::DAMAGE);
		sphere3->color = { 1,0,0,1 };

		Sphere* sphere4 = new Sphere(2.5);
		sphere4->SetPos(200, 25, 90);
		primitives.PushBack(sphere4);
		App->physics->AddBody(*sphere4, 10.0f, ElementType::DAMAGE);
		sphere4->color = { 1,0,0,1 };

		Sphere* sphere5 = new Sphere(2.5);
		sphere5->SetPos(190, 25, 90);
		primitives.PushBack(sphere5);
		App->physics->AddBody(*sphere5, 10.0f, ElementType::DAMAGE);
		sphere5->color = { 1,0,0,1 };

		spawnedBalls1 = true;
	}
	else if (body1->type == ElementType::SPAWN_SENSOR && body1->isSensor && spawnedBalls2 == false)
	{
		Sphere* sphere6 = new Sphere(2);
		sphere6->SetPos(210, 24, -55);
		primitives.PushBack(sphere6);
		App->physics->AddBody(*sphere6, 10.0f, ElementType::DAMAGE);
		sphere6->color = { 1,0,0,1 };

		spawnedBalls2 = true;
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
	App->physics->AddBody(*ground, 0.0f);
	ground->color = { 1,0,0,0 };

	// Ceiling (sky)
	// 1
	Cube* ceiling = new Cube(1000, 1, 1000);
	ceiling->SetPos(0, 300, 0);
	primitives.PushBack(ceiling);
	App->physics->AddBody(*ceiling, 0.0f);
	ceiling->color = { 0.4,0.9,1,1 };

	// Front wall (sky)
	// 2
	Cube* frontWall = new Cube(1000, 1000, 1);
	frontWall->SetPos(0, 0, 300);
	primitives.PushBack(frontWall);
	App->physics->AddBody(*frontWall, 0.0f);
	frontWall->color = { 0.4,0.9,1,1 };

	// Back wall (sky)
	// 3
	Cube* backWall = new Cube(1, 1000, 1000);
	backWall->SetPos(-300, 0, 0);
	primitives.PushBack(backWall);
	App->physics->AddBody(*backWall, 0.0f);
	backWall->color = { 0.4,0.9,1,1 };

	// Left wall (sky)
	// 4
	Cube* leftWall = new Cube(1, 1000, 1000);
	leftWall->SetPos(300, 0, 0);
	primitives.PushBack(leftWall);
	App->physics->AddBody(*leftWall, 0.0f);
	leftWall->color = { 0.4,0.9,1,1 };

	// Right wall (sky)
	// 5
	Cube* rightWall = new Cube(1000, 1000, 1);
	rightWall->SetPos(0, 0, -300);
	primitives.PushBack(rightWall);
	App->physics->AddBody(*rightWall, 0.0f);
	rightWall->color = { 0.4,0.9,1,1 };

	// Initial tunel
	// Left part
	// 6
	Cube* tunel = new Cube(1, 10, 100);
	tunel->SetPos(5, 5, 50);
	primitives.PushBack(tunel);
	App->physics->AddBody(*tunel, 0.0f);

	// Right part
	// 7
	Cube* tunel2 = new Cube(1, 10, 100);
	tunel2->SetPos(-5, 5, 50);
	primitives.PushBack(tunel2);
	App->physics->AddBody(*tunel2, 0.0f);

	// Ramp up
	// 8
	Cube* rampUp = new Cube(10, 100, 1);
	rampUp->SetPos(0, 1, 30);
	rampUp->SetRotation(75, { 1,0,0 });
	primitives.PushBack(rampUp);
	rampUp->color = { 0.25,0.25,0.25,1 };
	App->physics->AddBody(*rampUp, 0.0f);

	// Ramp down
	// 9
	Cube* rampDown = new Cube(10, 30, 1);
	rampDown->SetPos(0, 10, 130);
	rampDown->SetRotation(285, { 1,0,0 });
	primitives.PushBack(rampDown);
	rampDown->color = { 0.25,0.25,0.25 };
	App->physics->AddBody(*rampDown, 0.0f);

	// Ramp jump
	// 10
	Cube* rampJump = new Cube(10, 5, 1);
	rampJump->SetPos(0, 8, 140);
	rampJump->SetRotation(75, { 1,0,0 });
	primitives.PushBack(rampJump);
	rampJump->color = { 0.25,0.25,0.25 };
	App->physics->AddBody(*rampJump, 0.0f);

	// Cube to stop the car (Checkpoint)
	// Base
	// 11
	Cube* stopBase = new Cube(60, 1, 15);
	stopBase->SetPos(22.5, 5, 175);
	primitives.PushBack(stopBase);
	App->physics->AddBody(*stopBase, 0.0f);

	// Wall
	// 12
	Cube* stopWall = new Cube(15, 15, 1);
	stopWall->SetPos(0, 12.5, 182.5);
	primitives.PushBack(stopWall);
	App->physics->AddBody(*stopWall, 0.0f);

	// Fence
	// 13
	Cube* stopFence = new Cube(15, 2, 1);
	stopFence->SetPos(0, 6, 167.5);
	primitives.PushBack(stopFence);
	App->physics->AddBody(*stopFence, 0.0f);

	// Platforms to jump on
	// 14
	Cube* platform = new Cube(30, 1, 15);
	platform->SetPos(97.5, 10, 175);
	primitives.PushBack(platform);
	App->physics->AddBody(*platform, 0.0f);

	// 15
	Cube* platform2 = new Cube(45, 1, 15);
	platform2->SetPos(157.5, 12.5, 175);
	primitives.PushBack(platform2);
	App->physics->AddBody(*platform2, 0.0f);

	// Tube
	// 16
	Cube* tube = new Cube(15, 10, 1);
	tube->SetPos(210, 13.25, 167.5);
	primitives.PushBack(tube);
	App->physics->AddBody(*tube, 0.0f);

	// 17
	Cube* tube2 = new Cube(15, 15, 1);
	tube2->SetPos(210, 10.75, 182.5);
	primitives.PushBack(tube2);
	App->physics->AddBody(*tube2, 0.0f);

	// 18
	Cube* tube3 = new Cube(1, 15, 15);
	tube3->SetPos(202.5, 10.75, 175);
	primitives.PushBack(tube3);
	App->physics->AddBody(*tube3, 0.0f);

	// 19
	Cube* tube4 = new Cube(1, 30, 15);
	tube4->SetPos(217.5, 18.25, 175);
	primitives.PushBack(tube4);
	App->physics->AddBody(*tube4, 0.0f);

	// 20
	// Under tube platform
	Cube* tubePlatform = new Cube(15, 1, 15);
	tubePlatform->SetPos(210, 1, 175);
	primitives.PushBack(tubePlatform);
	App->physics->AddBody(*tubePlatform, 0.0f);

	// 21
	// Tube sensor
	Cube* tubeSensor = new Cube(15, 1, 15);
	tubeSensor->SetPos(210, 5, 175);
	tubeSensor->wire = true;
	primitives.PushBack(tubeSensor);
	App->physics->AddBody(*tubeSensor, 0.0f, ElementType::TUBE_SENSOR, this, true);

	// 22
	// Bounds
	Cube* platform11 = new Cube(15, 2, 1);
	platform11->SetPos(210, 1, 182.5);
	primitives.PushBack(platform11);
	App->physics->AddBody(*platform11, 0.0f);

	// 23
	Cube* platform12 = new Cube(1, 2, 15);
	platform12->SetPos(202.5, 1, 175);
	primitives.PushBack(platform12);
	App->physics->AddBody(*platform12, 0.0f);

	// 24
	Cube* platform13 = new Cube(1, 2, 15);
	platform13->SetPos(217.5, 1, 175);
	primitives.PushBack(platform13);
	App->physics->AddBody(*platform13, 0.0f);

	// 25
	Cube* platform14 = new Cube(15, 1, 15);
	platform14->SetPos(210, 3, 161);
	platform14->SetRotation(15, { 1,0,0 });
	primitives.PushBack(platform14);
	App->physics->AddBody(*platform14, 0.0f);

	// 26
	Cube* platform15 = new Cube(60, 1, 60);
	platform15->SetPos(210, 10, 115);
	platform15->SetRotation(15, { 1,0,0 });
	primitives.PushBack(platform15);
	App->physics->AddBody(*platform15, 0.0f);

	// 27
	// Balls sensor (at jump)
	Cube* platform16 = new Cube(15, 15, 1);
	platform16->SetPos(210, 5, 155);
	platform16->wire = true;
	primitives.PushBack(platform16);
	App->physics->AddBody(*platform16, 0.0f, ElementType::SPAWN_SENSOR, this, true);

	// Balls for constraints links
	// 28
	Sphere* sphere = new Sphere(1);
	sphere->SetPos(0, 28, 90);
	primitives.PushBack(sphere);
	App->physics->AddBody(*sphere, 0.0f, ElementType::DAMAGE);
	sphere->color = { 1,0,0,1 };

	// 29
	Sphere* sphere2 = new Sphere(2.5);
	sphere2->SetPos(0, 20, 90);
	primitives.PushBack(sphere2);
	App->physics->AddBody(*sphere2, 100.0f, ElementType::DAMAGE);
	sphere2->body->Push(1000.0f, 0.0f, 0.0f);
	sphere2->color = { 1,0,0,1 };

	// Platforms to jump
	Cube* platform3 = new Cube(15, 1, 15);
	platform3->SetPos(210, 20, 25);
	primitives.PushBack(platform3);
	App->physics->AddBody(*platform3, 0.0f);

	Cube* platform4 = new Cube(15, 1, 25);
	platform4->SetPos(210, 5, 10);
	primitives.PushBack(platform4);
	App->physics->AddBody(*platform4, 0.0f);

	// Sensor to spawn trap ball
	Cube* platform17 = new Cube(5, 5, 1);
	platform17->SetPos(210, 5, 5);
	platform17->wire = true;
	primitives.PushBack(platform17);
	App->physics->AddBody(*platform17, 0.0f, ElementType::SPAWN_SENSOR, this, true);

	// Rails
	Cube* rail = new Cube(1, 1, 15);
	rail->SetPos(208.5, 5, -10);
	primitives.PushBack(rail);
	App->physics->AddBody(*rail, 0.0f);

	Cube* rail2 = new Cube(1, 1, 15);
	rail2->SetPos(211.5, 5, -10);
	primitives.PushBack(rail2);
	App->physics->AddBody(*rail2, 0.0f);

	Cube* rail3 = new Cube(1, 1, 45);
	rail3->SetPos(208.5, 14.5, -37.5);
	rail3->SetRotation(25, { 1,0,0 });
	primitives.PushBack(rail3);
	App->physics->AddBody(*rail3, 0.0f);

	Cube* rail4 = new Cube(1, 1, 45);
	rail4->SetPos(211.5, 14.5, -37.5);
	rail4->SetRotation(25, { 1,0,0 });
	primitives.PushBack(rail4);
	App->physics->AddBody(*rail4, 0.0f);

	// Mini platform after rails
	Cube* platform5 = new Cube(7, 1, 13);
	platform5->SetPos(210, 24, -64);
	primitives.PushBack(platform5);
	App->physics->AddBody(*platform5, 0.0f);

	// Ending platform (?)
	Cube* platform6 = new Cube(12, 1, 12);
	platform6->SetPos(210, 15, -100);
	primitives.PushBack(platform6);
	App->physics->AddBody(*platform6, 0.0f);

	// Balls for constraints links
	Sphere* sphere3 = new Sphere(1);
	sphere3->SetPos(210, 33, 45);
	primitives.PushBack(sphere3);
	App->physics->AddBody(*sphere3, 0.0f, ElementType::DAMAGE);
	sphere3->color = { 1,0,0,1 };

	Sphere* sphere4 = new Sphere(2.5);
	sphere4->SetPos(210, 25, 45);
	primitives.PushBack(sphere4);
	App->physics->AddBody(*sphere4, 100.0f, ElementType::DAMAGE);
	sphere4->body->Push(1000.0f, 0.0f, 0.0f);
	sphere4->color = { 1,0,0,1 };

	App->physics->AddConstraintP2P(*sphere->body, *sphere2->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere->transform.translation().x - sphere2->transform.translation().x, sphere->transform.translation().y - sphere2->transform.translation().y, sphere->transform.translation().z - sphere2->transform.translation().z });
	App->physics->AddConstraintP2P(*sphere3->body, *sphere4->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere3->transform.translation().x - sphere4->transform.translation().x, sphere3->transform.translation().y - sphere4->transform.translation().y, sphere4->transform.translation().z - sphere4->transform.translation().z });

	// Reset / Checkpoint
	/*Cube* finishLine = new Cube(30, 20, 5);
	finishLine->SetPos(0, 10, 180);
	primitives.PushBack(finishLine);
	App->physics->AddBody(*finishLine, 0.0f, true, this);
	finishLine->color = { 0.0,1.0,0.0,1.0 };*/
}