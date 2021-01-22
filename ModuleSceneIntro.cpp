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
	else if (body1->type == ElementType::SPAWN_SENSOR_RAMP && body1->isSensor && spawnedBalls1 == false)
	{
		Sphere* sphere = new Sphere(2);
		sphere->SetPos(230, 25, 90);
		primitives.PushBack(sphere);
		App->physics->AddBody(*sphere, 10.0f, ElementType::DAMAGE, App->player, true);
		sphere->color = { 1,0,0,1 };

		Sphere* sphere2 = new Sphere(2);
		sphere2->SetPos(220, 25, 90);
		primitives.PushBack(sphere2);
		App->physics->AddBody(*sphere2, 10.0f, ElementType::DAMAGE, App->player, true);
		sphere2->color = { 1,0,0,1 };

		Sphere* sphere3 = new Sphere(2);
		sphere3->SetPos(210, 25, 90);
		primitives.PushBack(sphere3);
		App->physics->AddBody(*sphere3, 10.0f, ElementType::DAMAGE, App->player, true);
		sphere3->color = { 1,0,0,1 };

		Sphere* sphere4 = new Sphere(2);
		sphere4->SetPos(200, 25, 90);
		primitives.PushBack(sphere4);
		App->physics->AddBody(*sphere4, 10.0f, ElementType::DAMAGE, App->player, true);
		sphere4->color = { 1,0,0,1 };

		Sphere* sphere5 = new Sphere(2);
		sphere5->SetPos(190, 25, 90);
		primitives.PushBack(sphere5);
		App->physics->AddBody(*sphere5, 10.0f, ElementType::DAMAGE, App->player, true);
		sphere5->color = { 1,0,0,1 };

		spawnedBalls1 = true;
	}
	else if (body1->type == ElementType::SPAWN_SENSOR_RAIL && body1->isSensor && spawnedBalls2 == false)
	{
		Sphere* sphere6 = new Sphere(2);
		sphere6->SetPos(210, 24, -55);
		primitives.PushBack(sphere6);
		App->physics->AddBody(*sphere6, 10.0f, ElementType::DAMAGE, App->player, true);
		sphere6->color = { 1,0,0,1 };

		spawnedBalls2 = true;
	}
	else if (body1->type == ElementType::FINISH && body1->isSensor)
	{
		checkpoint = 0;

		spawnedBalls1 = false;
		spawnedBalls2 = false;

		primitives[16]->wire = false;
		primitives[17]->wire = false;
		primitives[18]->wire = false;
		primitives[19]->wire = false;
	}
	else if (body1->type == ElementType::CHECKPOINT && body1->isSensor && checkpoint == 0)
	{
		checkpoint = 1;
	}
	else if (body1->type == ElementType::CHECKPOINT2 && body1->isSensor && checkpoint == 1)
	{
		checkpoint = 2;
	}
	else if (body1->type == ElementType::CHECKPOINT3 && body1->isSensor && checkpoint == 2)
	{
		checkpoint = 3;
	}
	else if (body1->type == ElementType::CHECKPOINT4 && body1->isSensor && checkpoint == 3)
	{
		checkpoint = 4;
	}
}

void ModuleSceneIntro::CreateCircuit()
{
	// Building scenario

	// Ground (lava)
	// 0
	Cube* ground = new Cube(700, 1, 700);
	ground->SetPos(0, 0, 0);
	primitives.PushBack(ground);
	App->physics->AddBody(*ground, 0.0f, ElementType::DAMAGE, App->player);
	ground->color = { 1,0,0,1 };

	// Ceiling (sky)
	// 1
	Cube* ceiling = new Cube(500, 1, 500);
	ceiling->SetPos(100, 80, 0);
	primitives.PushBack(ceiling);
	App->physics->AddBody(*ceiling, 0.0f, ElementType::DAMAGE, App->player);
	ceiling->color = { 0.4,0.9,1,1 };

	// Front wall (sky)
	// 2
	Cube* frontWall = new Cube(500, 100, 1);
	frontWall->SetPos(100, 50, 200);
	primitives.PushBack(frontWall);
	App->physics->AddBody(*frontWall, 0.0f, ElementType::DAMAGE, App->player);
	frontWall->color = { 0.4,0.9,1,1 };

	// Back wall (sky)
	// 3
	Cube* backWall = new Cube(1, 100, 500);
	backWall->SetPos(-50, 50, 0);
	primitives.PushBack(backWall);
	App->physics->AddBody(*backWall, 0.0f, ElementType::DAMAGE, App->player);
	backWall->color = { 0.4,0.9,1,1 };

	// Left wall (sky)
	// 4
	Cube* leftWall = new Cube(1, 100, 500);
	leftWall->SetPos(300, 50, 0);
	primitives.PushBack(leftWall);
	App->physics->AddBody(*leftWall, 0.0f, ElementType::DAMAGE, App->player);
	leftWall->color = { 0.4,0.9,1,1 };

	// Right wall (sky)
	// 5
	Cube* rightWall = new Cube(500, 100, 1);
	rightWall->SetPos(100, 50, -150);
	primitives.PushBack(rightWall);
	App->physics->AddBody(*rightWall, 0.0f, ElementType::DAMAGE, App->player);
	rightWall->color = { 0.4,0.9,1,1 };

	// Initial tunel
	// Left part
	// 6
	Cube* tunel = new Cube(1, 10, 100);
	tunel->SetPos(5, 5, 10.5);
	primitives.PushBack(tunel);
	App->physics->AddBody(*tunel, 0.0f);

	// Right part
	// 7
	Cube* tunel2 = new Cube(1, 10, 100);
	tunel2->SetPos(-5, 5, 10.5);
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

	// Under tube platform
	// 20
	Cube* tubePlatform = new Cube(15, 1, 15);
	tubePlatform->SetPos(210, 1, 175);
	primitives.PushBack(tubePlatform);
	App->physics->AddBody(*tubePlatform, 0.0f);

	// Tube sensor
	// 21
	Cube* tubeSensor = new Cube(15, 1, 15);
	tubeSensor->SetPos(210, 10, 175);
	tubeSensor->wire = true;
	primitives.PushBack(tubeSensor);
	App->physics->AddBody(*tubeSensor, 0.0f, ElementType::TUBE_SENSOR, this, true);

	// Bounds
	// 22
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
	platform14->color = { 0.25,0.25,0.25,1 };
	App->physics->AddBody(*platform14, 0.0f);

	// 26
	Cube* platform15 = new Cube(60, 1, 60);
	platform15->SetPos(210, 10, 115);
	platform15->SetRotation(15, { 1,0,0 });
	primitives.PushBack(platform15);
	platform15->color = { 0.25,0.25,0.25,1 };
	App->physics->AddBody(*platform15, 0.0f);

	// Balls sensor (at jump)
	// 27
	Cube* platform16 = new Cube(15, 5, 1);
	platform16->SetPos(210, 10, 155);
	platform16->wire = true;
	primitives.PushBack(platform16);
	App->physics->AddBody(*platform16, 0.0f, ElementType::SPAWN_SENSOR_RAMP, this, true);

	// Balls for constraints links
	// 28
	Sphere* sphere = new Sphere(1);
	sphere->SetPos(0, 50, 90);
	primitives.PushBack(sphere);
	App->physics->AddBody(*sphere, 0.0f);

	// 29
	Sphere* sphere2 = new Sphere(2.5);
	sphere2->SetPos(0, 20, 90);
	primitives.PushBack(sphere2);
	App->physics->AddBody(*sphere2, 100.0f);
	sphere2->body->Push(1500.0f, 0.0f, 0.0f);
	sphere2->color = { 1,1,0,1 };

	// Platforms to jump
	// 30
	Cube* platform3 = new Cube(15, 1, 15);
	platform3->SetPos(210, 20, 25);
	primitives.PushBack(platform3);
	App->physics->AddBody(*platform3, 0.0f);

	// 31
	Cube* platform4 = new Cube(15, 1, 25);
	platform4->SetPos(210, 5, 10);
	primitives.PushBack(platform4);
	App->physics->AddBody(*platform4, 0.0f);

	// Sensor to spawn trap ball
	// 32
	Cube* trapBallSensor = new Cube(5, 5, 1);
	trapBallSensor->SetPos(210, 5, 5);
	trapBallSensor->wire = true;
	primitives.PushBack(trapBallSensor);
	App->physics->AddBody(*trapBallSensor, 0.0f, ElementType::SPAWN_SENSOR_RAIL, this, true);

	// Rails
	// 33
	Cube* rail = new Cube(1, 1, 15);
	rail->SetPos(208.5, 5, -10);
	primitives.PushBack(rail);
	App->physics->AddBody(*rail, 0.0f);

	// 34
	Cube* rail2 = new Cube(1, 1, 15);
	rail2->SetPos(211.5, 5, -10);
	primitives.PushBack(rail2);
	App->physics->AddBody(*rail2, 0.0f);

	// 35
	Cube* rail3 = new Cube(1, 1, 45);
	rail3->SetPos(208.5, 14.5, -37.5);
	rail3->SetRotation(25, { 1,0,0 });
	primitives.PushBack(rail3);
	App->physics->AddBody(*rail3, 0.0f);

	// 36
	Cube* rail4 = new Cube(1, 1, 45);
	rail4->SetPos(211.5, 14.5, -37.5);
	rail4->SetRotation(25, { 1,0,0 });
	primitives.PushBack(rail4);
	App->physics->AddBody(*rail4, 0.0f);

	// Mini platform after rails
	// 37
	Cube* platform5 = new Cube(7, 1, 13);
	platform5->SetPos(210, 24, -64);
	primitives.PushBack(platform5);
	App->physics->AddBody(*platform5, 0.0f);

	// Platform to jump on
	// 38
	Cube* platform6 = new Cube(15, 1, 15);
	platform6->SetPos(210, 15, -100);
	primitives.PushBack(platform6);
	App->physics->AddBody(*platform6, 0.0f);

	// Balls for constraints links
	// 39
	Sphere* sphere3 = new Sphere(1);
	sphere3->SetPos(210, 55, 45);
	primitives.PushBack(sphere3);
	App->physics->AddBody(*sphere3, 0.0f);

	// 40
	Sphere* sphere4 = new Sphere(3.5);
	sphere4->SetPos(210, 25, 45);
	primitives.PushBack(sphere4);
	App->physics->AddBody(*sphere4, 100.0f);
	sphere4->body->Push(1500.0f, 0.0f, 0.0f);
	sphere4->color = { 1,1,0,1 };

	// Initial platform
	// 41
	Cube* initPlatform = new Cube(9, 1, 135);
	initPlatform->SetPos(0, 1, -37.5);
	primitives.PushBack(initPlatform);
	App->physics->AddBody(*initPlatform, 0.0f);

	// Initial sensor
	// 42
	Cube* initSensor = new Cube(1, 1, 1);
	initSensor->SetPos(0, 3, 5);
	primitives.PushBack(initSensor);
	App->physics->AddBody(*initSensor, 0.0f, ElementType::FINISH, this, true);
	initSensor->wire = true;

	// Death catwalk
	Cube* catwalk = new Cube(50, 1, 15);
	catwalk->SetPos(150, 11, -100);
	primitives.PushBack(catwalk);
	App->physics->AddBody(*catwalk, 0.0f);

	// Square
	Cube* square = new Cube(30, 1, 30);
	square->SetPos(110, 11, -100);
	primitives.PushBack(square);
	App->physics->AddBody(*square, 0.0f);

	// Death catwalk 2
	Cube* catwalk2 = new Cube(50, 1, 15);
	catwalk2->SetPos(70, 11, -100);
	primitives.PushBack(catwalk2);
	App->physics->AddBody(*catwalk2, 0.0f);

	// Balls for constraints links
	// 28
	Sphere* sphere5 = new Sphere(1);
	sphere5->SetPos(150, 35, -100);
	primitives.PushBack(sphere5);
	App->physics->AddBody(*sphere5, 0.0f);

	// 29
	Sphere* sphere6 = new Sphere(3.5);
	sphere6->SetPos(150, 17, -100);
	primitives.PushBack(sphere6);
	App->physics->AddBody(*sphere6, 1000000.0f);
	sphere6->body->Push(-100000000.0f, 0.0f, 0.0f);
	sphere6->color = { 1,1,0,1 };

	// 30
	Sphere* sphere7 = new Sphere(10);
	sphere7->SetPos(110, 15, -100);
	primitives.PushBack(sphere7);
	App->physics->AddBody(*sphere7, 0.0f, ElementType::DAMAGE, this, true);
	sphere7->color = { 1,0,0,1 };

	// 31
	Sphere* sphere8 = new Sphere(1);
	sphere8->SetPos(90, 20, -100);
	primitives.PushBack(sphere8);
	App->physics->AddBody(*sphere8, 0.0f);

	// 32
	Sphere* sphere9 = new Sphere(1.5);
	sphere9->SetPos(90, 15, -100);
	primitives.PushBack(sphere9);
	App->physics->AddBody(*sphere9, 10.0f, ElementType::DAMAGE, App->player, true);
	sphere9->body->Push(0.0f, 0.0f, 1000.0f);
	sphere9->color = { 1,0,0,1 };

	// 33
	Sphere* sphere10 = new Sphere(1);
	sphere10->SetPos(70, 20, -100);
	primitives.PushBack(sphere10);
	App->physics->AddBody(*sphere10, 0.0f);

	// 34
	Sphere* sphere11 = new Sphere(1.5);
	sphere11->SetPos(70, 15, -100);
	primitives.PushBack(sphere11);
	App->physics->AddBody(*sphere11, 10.0f, ElementType::DAMAGE, App->player, true);
	sphere11->body->Push(0.0f, 0.0f, -1000.0f);
	sphere11->color = { 1,0,0,1 };

	// 35
	Sphere* sphere12 = new Sphere(1);
	sphere12->SetPos(50, 20, -100);
	primitives.PushBack(sphere12);
	App->physics->AddBody(*sphere12, 0.0f);

	// 36
	Sphere* sphere13 = new Sphere(1.5);
	sphere13->SetPos(50, 15, -100);
	primitives.PushBack(sphere13);
	App->physics->AddBody(*sphere13, 10.0f, ElementType::DAMAGE, App->player, true);
	sphere13->body->Push(0.0f, 0.0f, 1000.0f);
	sphere13->color = { 1,0,0,1 };

	// 37
	Cube* finalPlatform2 = new Cube(10, 10, 1);
	finalPlatform2->SetPos(0, 1, -105);
	primitives.PushBack(finalPlatform2);
	App->physics->AddBody(*finalPlatform2, 0.0f);

	// 38
	Cube* finalPlatform3 = new Cube(1, 10, 10);
	finalPlatform3->SetPos(5, 1, -100);
	primitives.PushBack(finalPlatform3);
	App->physics->AddBody(*finalPlatform3, 0.0f);

	// 39
	Cube* finalPlatform4 = new Cube(1, 10, 10);
	finalPlatform4->SetPos(-5, 1, -100);
	primitives.PushBack(finalPlatform4);
	App->physics->AddBody(*finalPlatform4, 0.0f);

	// Checkpoints
	// 40
	Cube* checkpoint = new Cube(1, 1, 1);
	checkpoint->SetPos(0, 7, 175);
	primitives.PushBack(checkpoint);
	App->physics->AddBody(*checkpoint, 0.0f, ElementType::CHECKPOINT, this, true);
	checkpoint->wire = true;

	// 41
	Cube* checkpoint2 = new Cube(1, 1, 1);
	checkpoint2->SetPos(210, 3, 175);
	primitives.PushBack(checkpoint2);
	App->physics->AddBody(*checkpoint2, 0.0f, ElementType::CHECKPOINT2, this, true);
	checkpoint2->wire = true;

	// 42
	Cube* checkpoint3 = new Cube(1, 1, 1);
	checkpoint3->SetPos(210, 22, 25);
	primitives.PushBack(checkpoint3);
	App->physics->AddBody(*checkpoint3, 0.0f, ElementType::CHECKPOINT3, this, true);
	checkpoint3->wire = true;

	// 43
	Cube* checkpoint4 = new Cube(1, 1, 1);
	checkpoint4->SetPos(210, 17, -100);
	primitives.PushBack(checkpoint4);
	App->physics->AddBody(*checkpoint4, 0.0f, ElementType::CHECKPOINT4, this, true);
	checkpoint4->wire = true;

	// Adding constraints
	App->physics->AddConstraintP2P(*sphere->body, *sphere2->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere->transform.translation().x - sphere2->transform.translation().x, sphere->transform.translation().y - sphere2->transform.translation().y, sphere->transform.translation().z - sphere2->transform.translation().z });
	App->physics->AddConstraintP2P(*sphere3->body, *sphere4->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere3->transform.translation().x - sphere4->transform.translation().x, sphere3->transform.translation().y - sphere4->transform.translation().y, sphere3->transform.translation().z - sphere4->transform.translation().z });
	App->physics->AddConstraintP2P(*sphere5->body, *sphere6->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere5->transform.translation().x - sphere6->transform.translation().x, sphere5->transform.translation().y - sphere6->transform.translation().y, sphere5->transform.translation().z - sphere6->transform.translation().z });
	App->physics->AddConstraintP2P(*sphere8->body, *sphere9->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere8->transform.translation().x - sphere9->transform.translation().x, sphere8->transform.translation().y - sphere9->transform.translation().y, sphere8->transform.translation().z - sphere9->transform.translation().z });
	App->physics->AddConstraintP2P(*sphere10->body, *sphere11->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere10->transform.translation().x - sphere11->transform.translation().x, sphere10->transform.translation().y - sphere11->transform.translation().y, sphere10->transform.translation().z - sphere11->transform.translation().z });
	App->physics->AddConstraintP2P(*sphere12->body, *sphere13->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere12->transform.translation().x - sphere13->transform.translation().x, sphere12->transform.translation().y - sphere13->transform.translation().y, sphere12->transform.translation().z - sphere13->transform.translation().z });
}