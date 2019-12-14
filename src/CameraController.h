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
class CameraController : public InputController
{
public:
    CameraController(Camera* camera);
    void keyboardInput(unsigned char key, int x,int y);
    void mouseInput(int button, int state, int x, int y);
    virtual ~CameraController();

private:
    int lastX_, lastY_;
    float moveSpeed_, rotationSpeed_;
    Camera* camera_;

    void translate(glm::vec3 const &offset); 
    void rotate(glm::quat const &rotation);
};

