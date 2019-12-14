#include "PhysxScene.h"

#define PX_RELEASE(x)	if(x)	{ x->release(); x = NULL; }

PhysxScene::PhysxScene(float gravity)
{
    foundation_ = PxCreateFoundation(PX_PHYSICS_VERSION, allocator_, errorCallback_);

    physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation_, PxTolerancesScale(), true);

    PxSceneDesc sceneDesc(physics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -gravity, 0.0f);
    dispatcher_ = PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = dispatcher_;
    sceneDesc.filterShader = PxDefaultSimulationFilterShader;
    scene = physics->createScene(sceneDesc);
}

PhysxScene::~PhysxScene()
{
    PX_RELEASE(scene);
    PX_RELEASE(dispatcher_);
    PX_RELEASE(physics);
    PX_RELEASE(foundation_);
}

void PhysxScene::step(float dt)
{
    scene->simulate(dt);
    scene->fetchResults(true);
}