#include "CameraControl.h"
#include "freeglut.h"

CameraControl::CameraControl(Camera* camera)
{
    lastX = -1;
    lastY = -1;
    this->camera = camera;
    moveSpeed = 1.f;
    rotationSpeed = glm::radians(10.f);
}

CameraControl::~CameraControl()
{
}

void CameraControl::keyboardInput(unsigned char key, int x, int y)
{
    glm::vec3 offset(0, 0, 0);
    float yaw = 0;

    switch (key)
    {
    case 'w': offset.z +=  moveSpeed; break;
    case 's': offset.z -=  moveSpeed; break;
    case 'd': offset.x += moveSpeed; break;
    case 'a': offset.x -= moveSpeed; break;
    case 'q': yaw += rotationSpeed; break;
    case 'e': yaw -= rotationSpeed; break;
    }

    if (offset != glm::vec3(0,0,0)) translate(offset);
    if (yaw != 0) rotate(glm::angleAxis(yaw, glm::vec3(0, 1, 0)));
}

void CameraControl::mouseInput(int button, int state, int x, int y)
{
    if (lastX < 0 || state == GLUT_DOWN) {
        lastX = x, lastY = y;
    }
    if (x == lastX && y == lastY) return;

    float scale = 0.05f;
    float angy = -(x - lastX) * rotationSpeed * scale;
    float angx = -(y - lastY) * rotationSpeed * scale;
    glm::quat rotx = glm::angleAxis(angx, camera->getSide());
    glm::quat roty = glm::angleAxis(angy, camera->getUp());
    rotate(roty * rotx);
    lastX = x;
    lastY = y;
}

void CameraControl::translate(glm::vec3 const & offset)
{
    glm::vec3 pos = camera->getPosition()
        + camera->getSide() * offset.x
        + camera->getDirection() * offset.z
        + camera->getUp() * offset.y;

    camera->setViewProperties(pos, camera->getDirection(), camera->getSide());
}

void CameraControl::rotate(glm::quat const & rotation)
{
    glm::vec3 dir = rotation * camera->getDirection();
    glm::vec3 side = glm::cross(dir, glm::vec3(0,1,0));
    camera->setViewProperties(camera->getPosition(), dir, side);
}
