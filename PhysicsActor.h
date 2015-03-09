#ifndef PHYSICSACTOR_H
#define PHYSICSACTOR_H

#include "Physics.h"

class PhysicsActor{
public:
	enum BODY_TYPE { CUBOID, SPHERE, STATIC_CUBOID, STATIC_SPHERE };

	PhysicsActor(hkpWorld* pWorld);
	~PhysicsActor();
	hkpRigidBody* getBody(){return mBody;}
	void createCuboid(hkVector4 position, hkVector4 halfExtents, bool isStatic = false, float mass = 1.f);
	void createSphere(hkVector4 position, hkReal radius, bool isStatic = false, float mass = 1.f);
protected:
	hkpWorld* physicsWorld;
	hkpRigidBody* mBody;
};

#endif