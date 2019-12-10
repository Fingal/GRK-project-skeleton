//==============================================================================================
//==============================================================================================
//
//         THIS IS A SKELETON CODE CLASS
//
//         DO NOT MODIFY IT !!!!!!!!!!!!!!!
//
//==============================================================================================
//==============================================================================================
#pragma once

#include "PxPhysicsAPI.h"
using namespace physx;

class PhysxScene
{
public:
    PhysxScene(float gravity);
    virtual ~PhysxScene();
    PxPhysics*              physics = nullptr;
    PxScene*				scene = nullptr;

    void step(float dt);

private:
    PxDefaultAllocator		allocator;
    PxDefaultErrorCallback	errorCallback;
    PxFoundation*			foundation = nullptr;
    PxDefaultCpuDispatcher*	dispatcher = nullptr;
};