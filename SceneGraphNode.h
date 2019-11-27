#pragma once
#include "glew.h"
#include "glm.hpp"

class SceneGraphNode
{
public:


	SceneGraphNode();
	SceneGraphNode(SceneGraphNode* parent);
	~SceneGraphNode();

	glm::mat4 getMatrix();
	glm::mat4 matrix;
private:
	SceneGraphNode* parent;
	bool is_root;
	float time;
	
};

