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
#include <map>
#include "glew.h"
#include "glm.hpp"
#include "ext.hpp"
#include "InputControl.h"
#include "Camera.h"
#include "SceneGraphNode.h"
#include "RenderObject.h"
#include "freeglut.h"
#include "RenderData.h"
using namespace std;

/*Class responsible for rendering scene seting camera and observing input*/
class Scene
{
public:
    Scene();
    virtual ~Scene();
    //adds object to render loop, returns its id
    // object - pointer to object
    int registerObject(RenderObject* object);
    //adds input conroller to render loop, returns its id
    // input - pointer to input conroller
    int registerInput(InputControl* input);

    //removes object from render loop found by its id
    void removeObject(int id);
    //removes conroller from render loop found by its id
    void removeInput(int id);

    //calculates matrices of all objects at given time, precalculation is required to syncronise objects movment
    void calculateMatrices(float time);

    //hook for keyboard input
    void keyboard(unsigned char key, int x, int y);

    //hook for mouse input
    void mouse(int button, int state, int x, int y);

    //sets main light source
    void setLight(glm::vec3 light);
    glm::vec3 getLight();
    void render();

    //sets scene camera
    void setCamera(Camera* camera);


private:
    map<unsigned int,InputControl*> inputControls;
    map<unsigned int, RenderObject*> renderObjects;
    Camera* camera;
    unsigned int lastIdObjects;
    unsigned int lastIdInput;
    glm::vec3 light;
};

