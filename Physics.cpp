#include "Physics.h"


Physics::Physics(void)
{
}


Physics::~Physics(void)
{
}

void Physics::SetUp(void)
{
	// Perfrom platform specific initialization for this demo - you should already have something similar in your own code.
	PlatformInit();

	// Need to have memory allocated for the solver. Allocate 1mb for it.
	hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault( hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(1024 * 1024) );
	hkBaseSystem::init( memoryRouter, errorReport );

	{
		hkpWorld* world = new hkpWorld( hkpWorldCinfo() );

		// Register all collision agents
		// It's important to register collision agents before adding any entities to the world.
		hkpAgentRegisterUtil::registerAllAgents( world->getCollisionDispatcher() );
		
		hkpRigidBody* rigidBody;
		{
			// Create a box 1 by 2 by 3
			hkVector4 halfExtents; halfExtents.set(0.5f, 1.0f, 1.5f);
			hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);

			hkpRigidBodyCinfo bodyCinfo;
			bodyCinfo.m_shape = boxShape;

			//  Calculate the mass properties for the shape
			const hkReal boxMass = 10.0f;
			hkMassProperties massProperties;
			hkpInertiaTensorComputer::computeShapeVolumeMassProperties(boxShape, boxMass, massProperties);

			bodyCinfo.setMassProperties(massProperties);

			// Create the rigid body
			rigidBody = new hkpRigidBody(bodyCinfo);

			// No longer need the reference on the boxShape, as the rigidBody now owns it
			boxShape->removeReference();
		}
		
		// Add the rigidBody to the world
		world->addEntity(rigidBody);

		// No longer need the ref of rigidBody - as the world now owns it
		rigidBody->removeReference();

		// Update as if running at 60 frames per second.
		const hkReal updateFrequency = 60.0f;
		for (int i = 0; i < 20; i++)
		{
			// Do some simulation steps
			world->stepDeltaTime(1.0f / updateFrequency);
		}

		// Release the reference on the world
		world->removeReference();
	}
	hkBaseSystem::quit();
	hkMemoryInitUtil::quit();

	return 0;
}
