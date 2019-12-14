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
#include "InputController.h"
#include "Camera.h"
#include "Renderable.h"
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
    int addRenderable(Renderable* renderable);

    //adds input conroller to render loop, returns its id
    // input - pointer to input conroller
    int addInput(InputController* input);

    //removes object from render loop found by its id
    void removeRenderable(int id);
    //removes conroller from render loop found by its id
    void removeInput(int id);

    //hook for keyboard input
    void keyboard(unsigned char key, int x, int y);

    //hook for mouse input
    void mouse(int button, int state, int x, int y);

    //sets main light source
    void setLight(glm::vec3 light);
    glm::vec3 getLight() const;
    
    // update scene
    void update(float time);

    // render scene
    void render();

    //sets scene camera
    void setCamera(Camera* camera);

private:
    map<unsigned int,InputController*> inputs_;
    map<unsigned int, Renderable*> renderables_;
    Camera* camera_ = nullptr;
    unsigned int nextRenderableId_ = 1;
    unsigned int nextInputId_ = 1;
    glm::vec3 light_;
};

