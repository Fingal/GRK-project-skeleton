#pragma once
#include "glew.h"
#include "glm.hpp"
#include "ext.hpp"
/*This class contains all data that is required to render object. If you need any more data put it here*/
class RenderData
{
public:
    glm::mat4 viewProjMatrix;
    glm::vec3 lightSource;
    RenderData();
    virtual ~RenderData();
};

