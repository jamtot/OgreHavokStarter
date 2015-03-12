#include "PhysicsActor.h"

PhysicsActor::PhysicsActor(hkpWorld* pWorld) : physicsWorld(pWorld) {

}

PhysicsActor::~PhysicsActor(){
	delete physicsWorld;
	delete mBody;
}

void PhysicsActor::createPCuboid(float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, bool isStatic, float mass){
	
	hkVector4 position(posX, posY, posZ);
	hkVector4 halfExtents(sizeX, sizeY, sizeZ);

	hkpBoxShape* shape = new hkpBoxShape(halfExtents);

	hkpRigidBodyCinfo bodyCinfo;
	bodyCinfo.m_shape = shape;
	bodyCinfo.m_position = position;

	if (isStatic) {
		bodyCinfo.m_motionType = hkpMotion::MOTION_FIXED;
		bodyCinfo.m_qualityType = HK_COLLIDABLE_QUALITY_FIXED;// default collision quality
	} else {
		//  Calculate the mass properties for the shape
		const hkReal mass = mass;
		hkMassProperties massProperties;
		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(shape, mass, massProperties);
		bodyCinfo.setMassProperties(massProperties);
	}

	// Create the rigid body
	mBody = new hkpRigidBody(bodyCinfo);

	// No longer need the reference on the shape, as mBody now owns it
	shape->removeReference();
	
	// Add the rigidBody to the world
	physicsWorld->addEntity(mBody);

}

void PhysicsActor::createPSphere(float posX, float posY, float posZ, float size, bool isStatic, float mass){
	hkVector4 position(posX, posY, posZ);
	hkReal radius = (size/2);
	hkpSphereShape* shape = new hkpSphereShape(radius);

	hkpRigidBodyCinfo bodyCinfo;
	bodyCinfo.m_shape = shape;
	bodyCinfo.m_position = position;

	if (isStatic) {
		bodyCinfo.m_motionType = hkpMotion::MOTION_FIXED;
		bodyCinfo.m_qualityType = HK_COLLIDABLE_QUALITY_FIXED;// default collision quality
	} else {
		//  Calculate the mass properties for the shape
		const hkReal mass = mass;
		hkMassProperties massProperties;
		hkpInertiaTensorComputer::computeShapeVolumeMassProperties(shape, mass, massProperties);
		bodyCinfo.setMassProperties(massProperties);
	}

	// Create the rigid body
	mBody = new hkpRigidBody(bodyCinfo);

	// No longer need the reference on the shape, as mBody now owns it
	shape->removeReference();
		
	// Add the rigidBody to the world
	physicsWorld->addEntity(mBody);
}