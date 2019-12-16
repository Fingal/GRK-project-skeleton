//==============================================================================================
//==============================================================================================
//
// This structure contains all data that is required to render object.
// If you need any more data put it here
//
//==============================================================================================
//==============================================================================================
#pragma once
#include "glew.h"
#include "glm.hpp"
#include "ext.hpp"

struct RenderData
{
    glm::mat4 viewProjMatrix;
    glm::vec3 lightSource;
};

