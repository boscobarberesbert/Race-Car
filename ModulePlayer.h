#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

// For text:
#include "Color.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glut/glut.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1200.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 500.0f

enum HUDStatus
{
	START,
	C1,
	C2,
	C3,
	C4,
	VICTORY,
	GAME_OVER
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CameraFollow();

	void ResetPosition();
	void ResetLevel();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void DrawTextHUD(float x, float y, float z, const char* text);

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	btTransform carPos;
	vec3 initialCarPos = { 0,0,0 };
	vec3 carDir = { 0,0,0 };
	vec3 cameraPos = { 0,0,0 };

	Timer lapTimer;
	int secondsPassed = 0;
	int minutesPassed = 0;

	HUDStatus currentHUD = HUDStatus::START;

private:

	float* initialTransf;

	Timer jumpCooldown;
};