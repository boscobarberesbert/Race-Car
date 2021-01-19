#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"

class btRigidBody;
class Module;

enum ElementType
{
	UNKNOWN,
	TUBE_SENSOR,
	SPAWN_SENSOR,
	DAMAGE,
	FINISH
};

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void ChangeSensor(bool isSensor);

private:
	btRigidBody* body = nullptr;

public:
	p2List<Module*> collision_listeners;

	bool isSensor = false;

	uint type = ElementType::UNKNOWN;
};

#endif // __PhysBody3D_H__