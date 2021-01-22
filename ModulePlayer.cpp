#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;

	secondsPassed = 0;
	minutesPassed = 0;

	currentHUD = HUDStatus::START;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(3.5, 1.5, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 300.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	
	vehicle->SetPos(0.0f, 3.0f, 5.0f);

	vehicle->collision_listeners.add(this);

	initialTransf = new float[16];
	vehicle->GetTransform(initialTransf);

	lapTimer.Start();
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		acceleration = -MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && jumpCooldown.ReadSec() >= 2.0f)
	{
		if (vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getY())
			vehicle->Jump(50000.0f);

		jumpCooldown.Start();
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && jumpCooldown.ReadSec() < 2.0f)
	{
		vehicle->vehicle->getRigidBody()->applyTorqueImpulse({ 0.0f, 10.0f, 0.0f });
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && jumpCooldown.ReadSec() < 2.0f)
	{
		vehicle->vehicle->getRigidBody()->applyTorqueImpulse({ 0.0f, -10.0f, 0.0f });
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		vehicle->vehicle->getRigidBody()->applyTorqueImpulse({ -500.0f * vehicle->vehicle->getForwardVector().getX(), -500.0f * vehicle->vehicle->getForwardVector().getY(), -500.0f * vehicle->vehicle->getForwardVector().getZ() });
	}
	
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		vehicle->vehicle->getRigidBody()->applyTorqueImpulse({ 500.0f * vehicle->vehicle->getForwardVector().getX(), 500.0f * vehicle->vehicle->getForwardVector().getY(), 500.0f * vehicle->vehicle->getForwardVector().getZ() });
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		ResetPosition();
	}

	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
	{
		currentHUD = HUDStatus::START;
		ResetLevel();
	}

	if (minutesPassed == 4)
	{
		currentHUD = HUDStatus::GAME_OVER;
		ResetLevel();
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	CameraFollow();

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	if(!App->debug)
		App->window->SetTitle(title);

	secondsPassed = int(lapTimer.ReadSec());
	if (secondsPassed == 59)
	{
		secondsPassed = 0;
		minutesPassed++;
		lapTimer.Start();
	}

	char hud[80];

	if (secondsPassed > 49)
	{
		sprintf_s(hud, "TIME REMAINING --- 0%d:0%d", (3 - minutesPassed), (59 - secondsPassed));
	}
	else
	{
		sprintf_s(hud, "TIME REMAINING --- 0%d:%d", (3 - minutesPassed), (59 - secondsPassed));
	}

	DrawTextHUD(
		vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getX() + 2.5f, 
		vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getY() + 7.0f, 
		vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getZ(),
		hud
	);

	switch (currentHUD)
	{
	case(HUDStatus::START):
		sprintf_s(hud, "START");
		break;
	case(HUDStatus::C1):
		sprintf_s(hud, "Checkpoint 1");
		break;
	case(HUDStatus::C2):
		sprintf_s(hud, "Checkpoint 2");
		break;
	case(HUDStatus::C3):
		sprintf_s(hud, "Checkpoint 3");
		break;
	case(HUDStatus::C4):
		sprintf_s(hud, "Checkpoint 4");
		break;
	case(HUDStatus::VICTORY):
		sprintf_s(hud, "YOU WIN!");
		break;
	case(HUDStatus::GAME_OVER):
		sprintf_s(hud, "YOU LOSE");
		break;
	}

	if ((currentHUD == HUDStatus::VICTORY || currentHUD == HUDStatus::GAME_OVER) && secondsPassed > 4)
	{
		currentHUD = HUDStatus::START;
	}

	DrawTextHUD(
		vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getX() + 2.5f,
		vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getY() + 6.5f,
		vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getZ(),
		hud
	);

	return UPDATE_CONTINUE;
}

void ModulePlayer::CameraFollow()
{
	carPos = vehicle->vehicle->getChassisWorldTransform();
	initialCarPos = { carPos.getOrigin().getX(),carPos.getOrigin().getY(),carPos.getOrigin().getZ() };
	carDir = { carPos.getBasis().getColumn(2).getX(),carPos.getBasis().getColumn(2).getY(),carPos.getBasis().getColumn(2).getZ() };
	App->camera->Position = cameraPos;
	cameraPos = initialCarPos - 15 * carDir;
	App->camera->Position.y = initialCarPos.y + 5;
}

void ModulePlayer::ResetPosition()
{
	if (App->scene_intro->checkpoint == 0)
	{
		vehicle->SetTransform(initialTransf);
	}
	else if (App->scene_intro->checkpoint == 1)
	{
		mat4x4 t;
		for (int i = 0; i < 16; i++)
		{
			t.M[i] = initialTransf[i];
		}
		t.rotate(90, vec3{ 0,1,0 });
		vehicle->SetTransform(t.M);
		vehicle->SetPos(0, 7, 175);
	}
	else if (App->scene_intro->checkpoint == 2)
	{
		mat4x4 t;
		for (int i = 0; i < 16; i++)
		{
			t.M[i] = initialTransf[i];
		}
		t.rotate(180, vec3{ 0,1,0 });
		vehicle->SetTransform(t.M);
		vehicle->SetPos(210, 3, 175);
	}
	else if (App->scene_intro->checkpoint == 3)
	{
		mat4x4 t;
		for (int i = 0; i < 16; i++)
		{
			t.M[i] = initialTransf[i];
		}
		t.rotate(180, vec3{ 0,1,0 });
		vehicle->SetTransform(t.M);
		vehicle->SetPos(210, 22, 25);
	}
	else if (App->scene_intro->checkpoint == 4)
	{
		mat4x4 t;
		for (int i = 0; i < 16; i++)
		{
			t.M[i] = initialTransf[i];
		}
		t.rotate(270, vec3{ 0,1,0 });
		vehicle->SetTransform(t.M);
		vehicle->SetPos(210, 17, -100);
	}

	vehicle->vehicle->getRigidBody()->clearForces();
	vehicle->vehicle->getRigidBody()->setLinearVelocity({ 0.0f,0.0f,0.0f });
	vehicle->vehicle->resetSuspension();
}

void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body2->type == ElementType::DAMAGE)
	{
		ResetPosition();
	}
}

void ModulePlayer::DrawTextHUD(float x, float y, float z, const char* text)
{
	glColor4b(255.0f, 255.0f, 255.0f, 255.0f);
	glRasterPos3f(x, y, z);
	int textLength = strlen(text);

	for (int i = 0; i < textLength; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}

void ModulePlayer::ResetLevel()
{
	minutesPassed = 0;
	secondsPassed = 0;
	lapTimer.Start();

	App->scene_intro->checkpoint = 0;

	ResetPosition();

	App->scene_intro->spawnedBalls1 = false;
	App->scene_intro->spawnedBalls2 = false;

	App->scene_intro->primitives[16]->wire = false;
	App->scene_intro->primitives[17]->wire = false;
	App->scene_intro->primitives[18]->wire = false;
	App->scene_intro->primitives[19]->wire = false;
}