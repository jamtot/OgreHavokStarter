#ifndef OGREACTOR_H
#define OGREACTOR_H

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
using namespace Ogre;

class OgreActor {
public:
	OgreActor(SceneManager * sceneMgr);
	~OgreActor();
	void trackPhysObj(Vector3 position, Quaternion newOgRot);
	void createOSphere(Vector3 position, Real size);
	void createOCuboid(Vector3 position, Vector3 halfWidths);
protected:
	SceneManager * m_sceneMgr;
	SceneNode* m_node;
};

#endif