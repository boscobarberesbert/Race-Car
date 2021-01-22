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
		Sphere* sphere1 = new Sphere(2);
		sphere1->SetPos(230, 25, 90);
		primitives.PushBack(sphere1);
		App->physics->AddBody(*sphere1, 10.0f, ElementType::DAMAGE);
		sphere1->color = { 1,0,0,1 };

		Sphere* sphere2 = new Sphere(2);
		sphere2->SetPos(220, 25, 90);
		primitives.PushBack(sphere2);
		App->physics->AddBody(*sphere2, 10.0f, ElementType::DAMAGE);
		sphere2->color = { 1,0,0,1 };

		Sphere* sphere3 = new Sphere(2);
		sphere3->SetPos(210, 25, 90);
		primitives.PushBack(sphere3);
		App->physics->AddBody(*sphere3, 10.0f, ElementType::DAMAGE);
		sphere3->color = { 1,0,0,1 };

		Sphere* sphere4 = new Sphere(2);
		sphere4->SetPos(200, 25, 90);
		primitives.PushBack(sphere4);
		App->physics->AddBody(*sphere4, 10.0f, ElementType::DAMAGE);
		sphere4->color = { 1,0,0,1 };

		Sphere* sphere5 = new Sphere(2);
		sphere5->SetPos(190, 25, 90);
		primitives.PushBack(sphere5);
		App->physics->AddBody(*sphere5, 10.0f, ElementType::DAMAGE);
		sphere5->color = { 1,0,0,1 };

		spawnedBalls1 = true;
	}
	else if (body1->type == ElementType::SPAWN_SENSOR_RAIL && body1->isSensor && spawnedBalls2 == false)
	{
		Sphere* sphere6 = new Sphere(2);
		sphere6->SetPos(210, 24, -55);
		primitives.PushBack(sphere6);
		App->physics->AddBody(*sphere6, 10.0f, ElementType::DAMAGE);
		sphere6->color = { 1,0,0,1 };

		spawnedBalls2 = true;
	}
	else if (body1->type == ElementType::FINISH && body1->isSensor && checkpoint == 4)
	{
		App->player->minutesPassed = 0;
		App->player->secondsPassed = 0;
		App->player->lapTimer.Start();
		checkpoint = 0;

		App->player->currentHUD = HUDStatus::VICTORY;

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
		App->player->currentHUD = HUDStatus::C1;
	}
	else if (body1->type == ElementType::CHECKPOINT2 && body1->isSensor && checkpoint == 1)
	{
		checkpoint = 2;
		App->player->currentHUD = HUDStatus::C2;
	}
	else if (body1->type == ElementType::CHECKPOINT3 && body1->isSensor && checkpoint == 2)
	{
		checkpoint = 3;
		App->player->currentHUD = HUDStatus::C3;
	}
	else if (body1->type == ElementType::CHECKPOINT4 && body1->isSensor && checkpoint == 3)
	{
		checkpoint = 4;
		App->player->currentHUD = HUDStatus::C4;
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
	App->physics->AddBody(*ground, 0.0f, ElementType::DAMAGE, this, true);
	ground->color = { 1,0,0,1 };

	// Ceiling (sky)
	// 1
	Cube* ceiling = new Cube(500, 1, 500);
	ceiling->SetPos(100, 80, 0);
	primitives.PushBack(ceiling);
	App->physics->AddBody(*ceiling, 0.0f, ElementType::DAMAGE);
	ceiling->color = { 0.4,0.9,1,1 };

	// Front wall (sky)
	// 2
	Cube* frontWall = new Cube(500, 100, 1);
	frontWall->SetPos(100, 50, 200);
	primitives.PushBack(frontWall);
	App->physics->AddBody(*frontWall, 0.0f, ElementType::DAMAGE);
	frontWall->color = { 0.4,0.9,1,1 };

	// Back wall (sky)
	// 3
	Cube* backWall = new Cube(1, 100, 500);
	backWall->SetPos(-50, 50, 0);
	primitives.PushBack(backWall);
	App->physics->AddBody(*backWall, 0.0f, ElementType::DAMAGE);
	backWall->color = { 0.4,0.9,1,1 };

	// Left wall (sky)
	// 4
	Cube* leftWall = new Cube(1, 100, 500);
	leftWall->SetPos(300, 50, 0);
	primitives.PushBack(leftWall);
	App->physics->AddBody(*leftWall, 0.0f, ElementType::DAMAGE);
	leftWall->color = { 0.4,0.9,1,1 };

	// Right wall (sky)
	// 5
	Cube* rightWall = new Cube(500, 100, 1);
	rightWall->SetPos(100, 50, -150);
	primitives.PushBack(rightWall);
	App->physics->AddBody(*rightWall, 0.0f, ElementType::DAMAGE);
	rightWall->color = { 0.4,0.9,1,1 };

	// Initial tunel
	// Left part
	// 6
	Cube* leftTunel = new Cube(1, 10, 100);
	leftTunel->SetPos(5, 5, 10.5);
	primitives.PushBack(leftTunel);
	App->physics->AddBody(*leftTunel, 0.0f);

	// Right part
	// 7
	Cube* rightTunel = new Cube(1, 10, 100);
	rightTunel->SetPos(-5, 5, 10.5);
	primitives.PushBack(rightTunel);
	App->physics->AddBody(*rightTunel, 0.0f);

	// Ramp up
	// 8
	Cube* rampUp = new Cube(10, 100, 1);
	rampUp->SetPos(0, 1, 30);
	rampUp->SetRotation(75, { 1,0,0 });
	primitives.PushBack(rampUp);
	App->physics->AddBody(*rampUp, 0.0f);
	rampUp->color = { 0.25,0.25,0.25,1 };

	// Ramp down
	// 9
	Cube* rampDown = new Cube(10, 30, 1);
	rampDown->SetPos(0, 10, 130);
	rampDown->SetRotation(285, { 1,0,0 });
	primitives.PushBack(rampDown);
	App->physics->AddBody(*rampDown, 0.0f);
	rampDown->color = { 0.25,0.25,0.25 };

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
	Cube* platformJump1 = new Cube(30, 1, 15);
	platformJump1->SetPos(97.5, 10, 175);
	primitives.PushBack(platformJump1);
	App->physics->AddBody(*platformJump1, 0.0f);

	// 15
	Cube* platformJump2 = new Cube(45, 1, 15);
	platformJump2->SetPos(157.5, 12.5, 175);
	primitives.PushBack(platformJump2);
	App->physics->AddBody(*platformJump2, 0.0f);

	// Tube
	// 16
	Cube* tube1 = new Cube(15, 10, 1);
	tube1->SetPos(210, 13.25, 167.5);
	primitives.PushBack(tube1);
	App->physics->AddBody(*tube1, 0.0f);

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

	// Under tube platform (Checkpoint)
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

	// Tube Bounds
	// 22
	Cube* tubeFence1 = new Cube(15, 2, 1);
	tubeFence1->SetPos(210, 1, 182.5);
	primitives.PushBack(tubeFence1);
	App->physics->AddBody(*tubeFence1, 0.0f);

	// 23
	Cube* tubeFence2 = new Cube(1, 2, 15);
	tubeFence2->SetPos(202.5, 1, 175);
	primitives.PushBack(tubeFence2);
	App->physics->AddBody(*tubeFence2, 0.0f);

	// 24
	Cube* tubeFence3 = new Cube(1, 2, 15);
	tubeFence3->SetPos(217.5, 1, 175);
	primitives.PushBack(tubeFence3);
	App->physics->AddBody(*tubeFence3, 0.0f);

	// 25
	Cube* tubeRamp = new Cube(15, 1, 15);
	tubeRamp->SetPos(210, 3, 161);
	tubeRamp->SetRotation(15, { 1,0,0 });
	primitives.PushBack(tubeRamp);
	App->physics->AddBody(*tubeRamp, 0.0f);
	tubeRamp->color = { 0.25,0.25,0.25,1 };

	// 26
	Cube* hugeRamp = new Cube(60, 1, 60);
	hugeRamp->SetPos(210, 10, 115);
	hugeRamp->SetRotation(15, { 1,0,0 });
	primitives.PushBack(hugeRamp);
	App->physics->AddBody(*hugeRamp, 0.0f);
	hugeRamp->color = { 0.25,0.25,0.25,1 };

	// Balls sensor (at jump)
	// 27
	Cube* ballsSensor = new Cube(15, 5, 1);
	ballsSensor->SetPos(210, 10, 155);
	ballsSensor->wire = true;
	primitives.PushBack(ballsSensor);
	App->physics->AddBody(*ballsSensor, 0.0f, ElementType::SPAWN_SENSOR_RAMP, this, true);

	// Balls for constraints links
	// 28
	Sphere* sphere1 = new Sphere(1);
	sphere1->SetPos(0, 50, 90);
	primitives.PushBack(sphere1);
	App->physics->AddBody(*sphere1, 0.0f);

	// 29
	Sphere* sphere2 = new Sphere(5);
	sphere2->SetPos(0, 20, 90);
	primitives.PushBack(sphere2);
	App->physics->AddBody(*sphere2, 100.0f);
	sphere2->body->Push(1500.0f, 0.0f, 0.0f);
	sphere2->color = { 1,1,0,1 };

	// Platforms to jump (Checkpoint)
	// 30
	Cube* landingPlatform1 = new Cube(15, 1, 15);
	landingPlatform1->SetPos(210, 20, 25);
	primitives.PushBack(landingPlatform1);
	App->physics->AddBody(*landingPlatform1, 0.0f);

	// 31 (Sensor Trap Ball)
	Cube* landingPlatform2 = new Cube(15, 1, 25);
	landingPlatform2->SetPos(210, 5, 10);
	primitives.PushBack(landingPlatform2);
	App->physics->AddBody(*landingPlatform2, 0.0f);

	// Sensor to spawn trap ball
	// 32
	Cube* trapBallSensor = new Cube(5, 5, 1);
	trapBallSensor->SetPos(210, 5, 5);
	trapBallSensor->wire = true;
	primitives.PushBack(trapBallSensor);
	App->physics->AddBody(*trapBallSensor, 0.0f, ElementType::SPAWN_SENSOR_RAIL, this, true);

	// Rails
	// 33
	Cube* rail1 = new Cube(1, 1, 15);
	rail1->SetPos(208.5, 5, -10);
	primitives.PushBack(rail1);
	App->physics->AddBody(*rail1, 0.0f);

	// 34
	Cube* rail2 = new Cube(1, 1, 15);
	rail2->SetPos(211.5, 5, -10);
	primitives.PushBack(rail2);
	App->physics->AddBody(*rail2, 0.0f);

	// 35 (Ramp)
	Cube* rail3 = new Cube(1, 1, 45);
	rail3->SetPos(208.5, 14.5, -37.5);
	rail3->SetRotation(25, { 1,0,0 });
	primitives.PushBack(rail3);
	App->physics->AddBody(*rail3, 0.0f);

	// 36 (Ramp)
	Cube* rail4 = new Cube(1, 1, 45);
	rail4->SetPos(211.5, 14.5, -37.5);
	rail4->SetRotation(25, { 1,0,0 });
	primitives.PushBack(rail4);
	App->physics->AddBody(*rail4, 0.0f);

	// Mini platform after rails
	// 37
	Cube* landingPlatform3 = new Cube(7, 1, 13);
	landingPlatform3->SetPos(210, 24, -64);
	primitives.PushBack(landingPlatform3);
	App->physics->AddBody(*landingPlatform3, 0.0f);

	// Platform to jump on (Checkpoint)
	// 38
	Cube* landingPlatform4 = new Cube(15, 1, 15);
	landingPlatform4->SetPos(210, 15, -100);
	primitives.PushBack(landingPlatform4);
	App->physics->AddBody(*landingPlatform4, 0.0f);

	// Balls for constraints links
	// 39
	Sphere* sphere3 = new Sphere(1);
	sphere3->SetPos(210, 55, 45);
	primitives.PushBack(sphere3);
	App->physics->AddBody(*sphere3, 0.0f);

	// 40
	Sphere* sphere4 = new Sphere(5);
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
	// 43
	Cube* catwalk1 = new Cube(50, 1, 15);
	catwalk1->SetPos(150, 11, -100);
	primitives.PushBack(catwalk1);
	App->physics->AddBody(*catwalk1, 0.0f);

	// Death catwalk Square
	// 44
	Cube* deathCatwalkSquare = new Cube(27, 1, 27);
	deathCatwalkSquare->SetPos(110, 11, -100);
	primitives.PushBack(deathCatwalkSquare);
	App->physics->AddBody(*deathCatwalkSquare, 0.0f);

	// Death catwalk
	// 45
	Cube* catwalk2 = new Cube(50, 1, 15);
	catwalk2->SetPos(70, 11, -100);
	primitives.PushBack(catwalk2);
	App->physics->AddBody(*catwalk2, 0.0f);

	// Balls for constraints links
	// 46
	Sphere* sphere5 = new Sphere(1);
	sphere5->SetPos(150, 47, -100);
	primitives.PushBack(sphere5);
	App->physics->AddBody(*sphere5, 0.0f);

	// 47
	Sphere* sphere6 = new Sphere(5);
	sphere6->SetPos(150, 17, -100);
	primitives.PushBack(sphere6);
	App->physics->AddBody(*sphere6, 1000000.0f);
	sphere6->body->Push(25000000.0f, 0.0f, 0.0f);
	sphere6->color = { 1,1,0,1 };

	// 48
	Sphere* sphere7 = new Sphere(10);
	sphere7->SetPos(110, 11, -100);
	primitives.PushBack(sphere7);
	App->physics->AddBody(*sphere7, 0.0f, ElementType::DAMAGE);
	sphere7->color = { 1,0,0,1 };

	// 49
	Sphere* sphere8 = new Sphere(1);
	sphere8->SetPos(90, 20, -100);
	primitives.PushBack(sphere8);
	App->physics->AddBody(*sphere8, 0.0f);

	// 50
	Sphere* sphere9 = new Sphere(1.5);
	sphere9->SetPos(90, 15, -100);
	primitives.PushBack(sphere9);
	App->physics->AddBody(*sphere9, 10.0f, ElementType::DAMAGE, App->player, true);
	sphere9->body->Push(0.0f, 0.0f, 100000.0f);
	sphere9->color = { 1,0,0,1 };

	// 51
	Sphere* sphere10 = new Sphere(1);
	sphere10->SetPos(70, 20, -100);
	primitives.PushBack(sphere10);
	App->physics->AddBody(*sphere10, 0.0f);

	// 52
	Sphere* sphere11 = new Sphere(1.5);
	sphere11->SetPos(70, 15, -100);
	primitives.PushBack(sphere11);
	App->physics->AddBody(*sphere11, 10.0f, ElementType::DAMAGE, App->player, true);
	sphere11->body->Push(0.0f, 0.0f, -100000.0f);
	sphere11->color = { 1,0,0,1 };

	// 53
	Sphere* sphere12 = new Sphere(1);
	sphere12->SetPos(50, 20, -100);
	primitives.PushBack(sphere12);
	App->physics->AddBody(*sphere12, 0.0f);

	// 54
	Sphere* sphere13 = new Sphere(1.5);
	sphere13->SetPos(50, 15, -100);
	primitives.PushBack(sphere13);
	App->physics->AddBody(*sphere13, 10.0f, ElementType::DAMAGE, App->player, true);
	sphere13->body->Push(0.0f, 0.0f, 100000.0f);
	sphere13->color = { 1,0,0,1 };

	// 55
	Cube* finalPlatform1 = new Cube(10, 10, 1);
	finalPlatform1->SetPos(0, 1, -105);
	primitives.PushBack(finalPlatform1);
	App->physics->AddBody(*finalPlatform1, 0.0f);

	// 56
	Cube* finalPlatform2 = new Cube(1, 10, 10);
	finalPlatform2->SetPos(5, 1, -100);
	primitives.PushBack(finalPlatform2);
	App->physics->AddBody(*finalPlatform2, 0.0f);

	// 57
	Cube* finalPlatform3 = new Cube(1, 10, 10);
	finalPlatform3->SetPos(-5, 1, -100);
	primitives.PushBack(finalPlatform3);
	App->physics->AddBody(*finalPlatform3, 0.0f);

	// Checkpoints
	// 58
	Cube* checkpoint = new Cube(1, 1, 1);
	checkpoint->SetPos(0, 7, 175);
	primitives.PushBack(checkpoint);
	App->physics->AddBody(*checkpoint, 0.0f, ElementType::CHECKPOINT, this, true);
	checkpoint->wire = true;

	// 59
	Cube* checkpoint2 = new Cube(1, 1, 1);
	checkpoint2->SetPos(210, 3, 175);
	primitives.PushBack(checkpoint2);
	App->physics->AddBody(*checkpoint2, 0.0f, ElementType::CHECKPOINT2, this, true);
	checkpoint2->wire = true;

	// 60
	Cube* checkpoint3 = new Cube(1, 1, 1);
	checkpoint3->SetPos(210, 22, 25);
	primitives.PushBack(checkpoint3);
	App->physics->AddBody(*checkpoint3, 0.0f, ElementType::CHECKPOINT3, this, true);
	checkpoint3->wire = true;

	// 61
	Cube* checkpoint4 = new Cube(1, 1, 1);
	checkpoint4->SetPos(210, 17, -100);
	primitives.PushBack(checkpoint4);
	App->physics->AddBody(*checkpoint4, 0.0f, ElementType::CHECKPOINT4, this, true);
	checkpoint4->wire = true;

	// Adding constraints
	App->physics->AddConstraintP2P(*sphere1->body, *sphere2->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere1->transform.translation().x - sphere2->transform.translation().x, sphere1->transform.translation().y - sphere2->transform.translation().y, sphere1->transform.translation().z - sphere2->transform.translation().z });
	App->physics->AddConstraintP2P(*sphere3->body, *sphere4->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere3->transform.translation().x - sphere4->transform.translation().x, sphere3->transform.translation().y - sphere4->transform.translation().y, sphere3->transform.translation().z - sphere4->transform.translation().z });
	App->physics->AddConstraintP2P(*sphere5->body, *sphere6->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere5->transform.translation().x - sphere6->transform.translation().x, sphere5->transform.translation().y - sphere6->transform.translation().y, sphere5->transform.translation().z - sphere6->transform.translation().z });
	App->physics->AddConstraintP2P(*sphere8->body, *sphere9->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere8->transform.translation().x - sphere9->transform.translation().x, sphere8->transform.translation().y - sphere9->transform.translation().y, sphere8->transform.translation().z - sphere9->transform.translation().z });
	App->physics->AddConstraintP2P(*sphere10->body, *sphere11->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere10->transform.translation().x - sphere11->transform.translation().x, sphere10->transform.translation().y - sphere11->transform.translation().y, sphere10->transform.translation().z - sphere11->transform.translation().z });
	App->physics->AddConstraintP2P(*sphere12->body, *sphere13->body, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ sphere12->transform.translation().x - sphere13->transform.translation().x, sphere12->transform.translation().y - sphere13->transform.translation().y, sphere12->transform.translation().z - sphere13->transform.translation().z });
}