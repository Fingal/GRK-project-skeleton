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
#include "glm.hpp"
#include "glew.h"
#include "glm.hpp"
#include "RenderData.h"

/*abstract render object*/
class Renderable
{
public:
    Renderable() {}
    virtual ~Renderable() {}

    virtual glm::mat4 getModelMatrix() const = 0;
    virtual void update(float time) = 0;
    virtual void render(RenderData& data) = 0;
};

