#pragma once
#include "glm.hpp"
#include "glew.h"
#include "glm.hpp"
#include "SceneGraphNode.h"
#include "RenderData.h"


/*abstracy render object*/
class RenderObject
{
public:
	RenderObject();
	//parent = object required for scene graph
	RenderObject(RenderObject* parent);
	~RenderObject();
	glm::mat4 getModelMatrix();
	virtual glm::mat4 getTransformationMarix();
	virtual glm::mat4 calculateTransformationMarix(float time);
	virtual void render(RenderData& data);
protected:
	SceneGraphNode*	graphNode;
};

