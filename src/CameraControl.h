#pragma once
#include "InputControl.h"
#include "Camera.h"
/*exemplary implementation for input control that controls given camera based on wsad keys and mouse click*/
class CameraControl :
    public InputControl
{
public:
    CameraControl(Camera* camera);
    void keyboardInput(unsigned char key, int x,int y);
    void mouseInput(int button, int state, int x, int y);
    virtual ~CameraControl();

private:
    int lastX, lastY;
    float moveSpeed, rotationSpeed;
    Camera* camera;

    void translate(glm::vec3 const &offset);
    void rotate(glm::quat const &rotation);
};

