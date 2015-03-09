#include "OgreActor.h"

OgreActor::OgreActor(){

}

OgreActor::~OgreActor(){
	delete m_node;
	delete m_sceneMgr;
}

void OgreActor::update(Vector3 position, Radian angleRot, Vector3 axisRot){
	//set the nodes position
	m_node->setPosition(position);
	//set its current rotation
	Quaternion newOgRot = Ogre::Quaternion(angleRot,axisRot);
	m_node->setOrientation(newOgRot);
}

void OgreActor::createSphere(Vector3 position, Real size) {
	Ogre::Entity* ogreSphere = m_sceneMgr->createEntity("Sphere", "sphere.mesh");
	m_node = m_sceneMgr->getRootSceneNode()->createChildSceneNode("SphereNode");//add a ID generator to this later to add more
	m_node->attachObject(ogreSphere);
	//get down to 1 unit size first, then multiply by size
	m_node->scale( (0.1*size), (0.1*size), (0.1*size) );
	m_node->setPosition(position);
}

void OgreActor::createCuboid(Vector3 position, Real size) {
	Ogre::Entity* ogreSphere = m_sceneMgr->createEntity("Sphere", "sphere.mesh");
	m_node = m_sceneMgr->getRootSceneNode()->createChildSceneNode("SphereNode");//add a ID generator to this later to add more
	m_node->attachObject(ogreSphere);
	//get down to 1 unit size first, then multiply by size
	m_node->scale( (0.1*size), (0.1*size), (0.1*size) );
	m_node->setPosition(position);
}