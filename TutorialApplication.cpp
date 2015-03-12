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
	physics.SetUp();

	//add plane physically, then graphically
	physics.addPlane();

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/Rockwall");
	entGround->setCastShadows(false);

	/*
	//add cube physically, then graphically
	physics.addCuboid();

	Ogre::Entity* ogreCube = mSceneMgr->createEntity("Cube", "cube.mesh");
	cubeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CubeNode");

	cubeNode->attachObject(ogreCube);
	cubeNode->scale(0.1,0.1,0.1);
	hkVector4 p(0,0,0);
	p = physics.getCubePosition();
	Ogre::Vector3 pos = Ogre::Vector3(p(0),p(1),p(2));
	cubeNode->setPosition(pos);
	*/

	Actor * sphereActor = new Actor(mSceneMgr, physics.GetPhysicsWorld() );
	sphereActor->createSphere(0,10,0,1);

	

	// Create a Light and set its position

	Ogre::Light* light = mSceneMgr->createLight("MainLight");

	light->setPosition(20.0f, 80.0f, 50.0f);


}

void TutorialApplication::destroyScene(void){
	physics.TidyUp();
	BaseApplication::destroyScene();
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt){

	physics.Simulate(evt.timeSinceLastFrame);

	hkVector4 p(0,0,0);
	p = physics.getCubePosition();
	Ogre::Vector3 pos = Ogre::Vector3(p(0),p(1),p(2));
	cubeNode->setPosition(pos);

	return BaseApplication::frameRenderingQueued(evt);
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
