#pragma once

#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Common/Base/Fwd/hkcstdio.h>

// Physics
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>

static void HK_CALL errorReport(const char* msg, void* userContext)
{
	using namespace std;
	printf("%s", msg);
}

class Physics
{
private:
	hkpWorld* physicsWorld;
	//hkJobQueue* jobQueue;
	//hkJobThreadPool* threadPool;
public:
	Physics(void);
	~Physics(void);

	hkpWorld* GetPhysicsWorld(){return physicsWorld;}
	void SetUp(void);
	
	void Simulate(float);
	void TidyUp(void);
};

// Keycode
#include <Common/Base/keycode.cxx>

// Productfeatures
// We're using only physics - we undef products even if the keycode is present so
// that we don't get the usual initialization for these products.
#undef HK_FEATURE_PRODUCT_AI
#undef HK_FEATURE_PRODUCT_ANIMATION
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION_2012
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_BEHAVIOR
#undef HK_FEATURE_PRODUCT_SIMULATION
#undef HK_FEATURE_PRODUCT_PHYSICS

// Also we're not using any serialization/versioning so we don't need any of these.
#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
#define HK_EXCLUDE_FEATURE_RegisterVersionPatches
//#define HK_EXCLUDE_FEATURE_RegisterReflectedClasses
#define HK_EXCLUDE_FEATURE_MemoryTracker

// This include generates an initialization function based on the products
// and the excluded features.
#include <Common/Base/Config/hkProductFeatures.cxx>

// Platform specific initialization
#include <Common/Base/System/Init/PlatformInit.cxx>