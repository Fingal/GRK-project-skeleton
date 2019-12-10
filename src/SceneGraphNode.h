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
#include "glew.h"
#include "glm.hpp"

class SceneGraphNode
{
public:
    SceneGraphNode();
    SceneGraphNode(SceneGraphNode* parent);
    virtual ~SceneGraphNode();

    glm::mat4 getMatrix();
    glm::mat4 matrix;

private:
    SceneGraphNode* parent;
    bool is_root;
    float time;

};

