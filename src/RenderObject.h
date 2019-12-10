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
#include "SceneGraphNode.h"
#include "RenderData.h"


/*abstract render object*/
class RenderObject
{
public:
    RenderObject();
    //parent = object required for scene graph
    RenderObject(RenderObject* parent);
    virtual ~RenderObject();
    glm::mat4 getModelMatrix();
	//abstract function that is supposed to return calculated matrix last time when calculateTransformationMarix was called
    virtual glm::mat4 getTransformationMarix();
	//abstract function that is supposed to calculate transformation matrix at given time.
    virtual glm::mat4 calculateTransformationMarix(float time);
	//abstract function that is supposed to do object render based on given data and calculated earlier matrix 
    virtual void render(RenderData& data);
protected:
    SceneGraphNode*	graphNode;
};

