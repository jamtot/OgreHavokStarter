#include "OgreActor.h"

OgreActor::OgreActor(SceneManager * sceneMgr) : m_sceneMgr(sceneMgr) {

}

OgreActor::~OgreActor(){
	delete m_node;
	delete m_sceneMgr;
}

void OgreActor::trackPhysObj(Vector3 position, Quaternion newOgRot){
	//set the nodes position
	m_node->setPosition(position);
	//set its current rotation
	m_node->setOrientation(newOgRot);
}

void OgreActor::createOSphere(Vector3 position, Real size) {
	Ogre::Entity* ogreSphere = m_sceneMgr->createEntity("Sphere", "sphere.mesh");
	m_node = m_sceneMgr->getRootSceneNode()->createChildSceneNode("SphereNode");//add a ID generator to this later to add more
	m_node->attachObject(ogreSphere);
	//get down to 1 unit size first, then multiply by size
	m_node->scale( (0.1*size), (0.1*size), (0.1*size) );
	m_node->setPosition(position);
}

void OgreActor::createOCuboid(Vector3 position, Vector3 halfWidths) {
	Ogre::Entity* ogreCuboid = m_sceneMgr->createEntity("Cube", "cube.mesh");
	m_node = m_sceneMgr->getRootSceneNode()->createChildSceneNode("CubeNode");//add a ID generator to this later to add more
	m_node->attachObject(ogreCuboid);
	//get down to 1 unit size first, then multiply by size
	m_node->scale( (0.1*halfWidths.x), (0.1*halfWidths.y), (0.1*halfWidths.z) );
	m_node->setPosition(position);
}