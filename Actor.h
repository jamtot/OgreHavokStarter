#pragma once
#include "OgreActor.h",
#include "PhysicsActor.h"
using namespace Ogre;
class Actor :
	public OgreActor,
	public PhysicsActor
{
public:
	Actor(SceneManager * sceneMgr, hkpWorld* pWorld);
	~Actor(void);

	void update(void);

	void createSphere(Vector3 position, Real size, bool isStatic = false, float mass = 1.0f);
	void createCuboid(Vector3 position, Vector3 halfWidths, bool isStatic = false, float mass = 1.0f);
	
private:
	
	bool isSet; //will track whether the actor has been initialised or not
};

