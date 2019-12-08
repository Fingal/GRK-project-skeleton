#include "CameraControl.h"
#include "freeglut.h"


CameraControl::CameraControl(Camera* camera)
{
    lastX = -1;
    lastY = -1;
    this->camera = camera;
    moveSpeed = 0.1;
}
void CameraControl::keyboardInput(unsigned char key, int x, int y)
{
    float side = 0;
    float dir = 0;
    float roll = 0;

    switch (key)
    {
    case 'w':
        dir +=  moveSpeed;
        break;
    case 's':
        dir -=  moveSpeed;
        break;
    case 'd':
        side += moveSpeed;
        break;
    case 'a':
        side -= moveSpeed;
        break;
    case 'q':
        roll += 1;
        break;
    case 'e':
        roll -= 1;
        break;
    }
    if (abs(roll) > 0.01)
    {
        glm::vec3 rotationChange(0.);
        rotationChange.z = 10* roll;
        this->camera->changeRotation(rotationChange);
    }
    camera->move(dir, side);
}

void CameraControl::mouseInput(int button, int state, int x, int y)
{
    if (lastX < 0 || state == GLUT_DOWN)
    {
        lastX = x;
        lastY = y;
    }
    glm::vec3 rotationChange(0.);
    rotationChange.y = (x - lastX);
    rotationChange.x = (y - lastY);
    lastX = x;
    lastY = y;
    this->camera->changeRotation(rotationChange);
}
CameraControl::~CameraControl()
{
}
