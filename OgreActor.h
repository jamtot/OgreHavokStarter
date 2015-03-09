#ifndef OGREACTOR_H
#define OGREACTOR_H

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
using namespace Ogre;

class OgreActor {
public:
	OgreActor();
	~OgreActor();
	void update(Vector3 position, Radian angleRot, Vector3 axisRot);
	void createSphere(Vector3 position, Real size);
	void createCuboid(Vector3 position, Real size);
protected:
	SceneManager * m_sceneMgr;
	SceneNode* m_node;
};

#endif