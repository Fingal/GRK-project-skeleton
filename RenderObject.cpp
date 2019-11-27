#include "RenderObject.h"



RenderObject::RenderObject()
{
	this->graphNode = new SceneGraphNode();
}

RenderObject::RenderObject(RenderObject* parent)
{
	this->graphNode = new SceneGraphNode(parent->graphNode);
}


RenderObject::~RenderObject()
{
	delete this->graphNode;
}

glm::mat4 RenderObject::getModelMatrix()
{
	return graphNode->getMatrix();
}

glm::mat4 RenderObject::calculateTransformationMarix(float time)
{
	graphNode->matrix = glm::mat4();
	return glm::mat4();
}

void RenderObject::render(RenderData& data)
{
}


glm::mat4 RenderObject::getTransformationMarix()
{
	return graphNode->matrix;
}
