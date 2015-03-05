/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
___                 __    __ _ _    _ 
/___\__ _ _ __ ___  / / /\ \ (_) | _(_)
//  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
|___/                              
Tutorial Framework
http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// create your scene here :)

	//ogre head example code
	// Set the scene's ambient light

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	// Create an Entity

	Ogre::Entity* ogreSphere = mSceneMgr->createEntity("Sphere", "sphere.mesh");

	Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/Rockwall");
	entGround->setCastShadows(false);

	// Create a SceneNode and attach the Entity to it

	Ogre::SceneNode* sphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("SphereNode");

	sphereNode->attachObject(ogreSphere);
	sphereNode->scale(0.1,0.1,0.1);
	sphereNode->setPosition(0.0, 10.0, 0.0);

	// Create a Light and set its position

	Ogre::Light* light = mSceneMgr->createLight("MainLight");

	light->setPosition(20.0f, 80.0f, 50.0f);


}

void TutorialApplication::destroyScene(void){

	BaseApplication::destroyScene();
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt){


	return BaseApplication::frameRenderingQueued(evt);
}

void TutorialApplication::setupPhysics(hkpWorld* physicsWorld)
{
	// Create the floor as a fixed box
	{
		hkpRigidBodyCinfo boxInfo;
		hkVector4 boxSize(5.0f, 0.5f , 5.0f);
		hkpBoxShape* boxShape = new hkpBoxShape(boxSize);
		boxInfo.m_shape = boxShape;
		boxInfo.m_motionType = hkpMotion::MOTION_FIXED;
		boxInfo.m_position.set(0.0f, 0.0f, 0.0f);
		boxInfo.m_restitution = 0.9f;

		hkpRigidBody* floor = new hkpRigidBody(boxInfo);
		boxShape->removeReference();

		physicsWorld->addEntity(floor);
		floor->removeReference();
	}

	// Create a moving sphere
	{
		hkReal sphereRadius = 0.5f;
		hkpConvexShape* sphereShape = new hkpSphereShape(sphereRadius);

		hkpRigidBodyCinfo sphereInfo;
		sphereInfo.m_shape = sphereShape;
		sphereInfo.m_position.set(0.0f, 5.0f, 0.0f);
		sphereInfo.m_motionType = hkpMotion::MOTION_SPHERE_INERTIA;

		// Compute mass properties
		hkReal sphereMass = 10.0f;
		hkMassProperties sphereMassProperties;
		hkpInertiaTensorComputer::computeSphereVolumeMassProperties(sphereRadius, sphereMass, sphereMassProperties);
		sphereInfo.m_inertiaTensor = sphereMassProperties.m_inertiaTensor;
		sphereInfo.m_centerOfMass = sphereMassProperties.m_centerOfMass;
		sphereInfo.m_mass = sphereMassProperties.m_mass;

		// Create sphere RigidBody
		hkpRigidBody* sphereRigidBody = new hkpRigidBody(sphereInfo);
		sphereShape->removeReference();

		physicsWorld->addEntity(sphereRigidBody);
		g_ball = sphereRigidBody;
		sphereRigidBody->removeReference();
	}
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
	int main(int argc, char *argv[])
#endif
	{
		// Create application object
		TutorialApplication app;

		try {
			app.go();
		} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif
