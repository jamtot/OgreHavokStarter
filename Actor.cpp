#include "Actor.h"


Actor::Actor(SceneManager * sceneMgr, hkpWorld* pWorld) 
	: OgreActor(sceneMgr), PhysicsActor(pWorld), isSet(false)
{
}


Actor::~Actor(void)
{
}

void Actor::update(void)
{
	hkVector4 p(0,0,0);
	p = mBody->getPosition();
	Vector3 pos = Vector3(p(0),p(1),p(2));
	m_node->setPosition(pos);

	hkQuaternion q; 
	q = hkQuaternion(mBody->getRotation());
	Radian angleRot = q.getAngle();

	hkVector4 axis = hkVector4(0,0,0);
	if(q.hasValidAxis())
		q.getAxis(axis); 

	Vector3 axisRot = Vector3(axis(0),axis(1),axis(2));

	Quaternion newOgRot = Ogre::Quaternion(angleRot,axisRot);

	//sets the ogre objects position and rotation to that of the physics object
	trackPhysObj(pos, newOgRot);
}

void Actor::createSphere(Vector3 position, Real size, bool isStatic, float mass)
{
	if (!isSet){
		createOSphere(position, size);
		createPSphere(hkVector4(position.x,position.y,position.z), size, isStatic, mass); 
		isSet = true;
	}
}

void Actor::createCuboid(Vector3 position, Vector3 halfWidths, bool isStatic, float mass)
{
	if (!isSet){
		createOCuboid(position, halfWidths);
		createPCuboid(hkVector4(position.x,position.y,position.z), hkVector4(halfWidths.x, halfWidths.y, halfWidths.z), isStatic, mass);
		isSet = true;
	}
}
