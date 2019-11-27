#include "SceneGraphNode.h"



SceneGraphNode::SceneGraphNode(){
	this->parent = 0;
	this->is_root = true;
}

SceneGraphNode::SceneGraphNode(SceneGraphNode* parent){
	this->parent = parent;
	this->is_root = false;
}

glm::mat4 SceneGraphNode::getMatrix() {
	if (is_root) {
		return matrix;
	}
	return this->parent->getMatrix()*matrix;
}

SceneGraphNode::~SceneGraphNode()
{
}

