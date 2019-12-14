//==============================================================================================
//==============================================================================================
//
//         EXAMPLE: CAMERA CONTROLLER
//
//==============================================================================================
//==============================================================================================
#pragma once
#include "InputController.h"
#include "Camera.h"

// Camera controller
// Use WSAD to move camera, QE to rotate it
// Use mouse click + drag to rotate
class ExampleCameraController : public InputController
{
public:
    ExampleCameraController();

    void setCamera(Camera *camera);

    void keyboardInput(unsigned char key, int x,int y);
    void mouseInput(int button, int state, int x, int y);
    virtual ~ExampleCameraController();

private:
    int lastX_ = -1, lastY_ = -1;
    float moveSpeed_, rotationSpeed_;
    Camera* camera_ = nullptr;

    void translate(glm::vec3 const &offset); 
    void rotate(glm::quat const &rotation);
};

