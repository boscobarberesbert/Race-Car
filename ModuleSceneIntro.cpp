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
		primitives[i]->Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateCircuit()
{
	// Building scenario
	Cube* platform = new Cube(10, 1, 100);
	platform->SetPos(0, 10, 148);
	primitives.PushBack(platform);
	App->physics->AddBody(*platform, 0.0f);
	platform->color = {0.2,0.2,0.2,1};

	Cube* platform2 = new Cube(2, 10, 100);
	platform2->SetPos(6, 10, 148);
	primitives.PushBack(platform2);
	App->physics->AddBody(*platform2, 0.0f);

	Cube* platform3 = new Cube(2, 10, 100);
	platform3->SetPos(-6, 10, 148);
	primitives.PushBack(platform3);
	App->physics->AddBody(*platform3, 0.0f);

	//ramp up
	Cube* rampUp = new Cube(10, 20, 1);
	rampUp->SetPos(0, 5, 90);
	rampUp->SetRotation(60, { 1,0,0 });
	primitives.PushBack(rampUp);
	rampUp->color = { 0.25,0.25,0.25 };
	App->physics->AddBody(*rampUp, 0.0f);

	//ramp up
	Cube* rampDown = new Cube(10, 20, 1);
	rampDown->SetPos(0, 5, 206);
	rampDown->SetRotation(300, { 1,0,0 });
	primitives.PushBack(rampDown);
	rampDown->color = { 0.25,0.25,0.25 };
	App->physics->AddBody(*rampDown, 0.0f);
}
