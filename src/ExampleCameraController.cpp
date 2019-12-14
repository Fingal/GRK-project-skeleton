//==============================================================================================
//==============================================================================================
//
//         EXAMPLE: CAMERA CONTROLLER
//
//==============================================================================================
//==============================================================================================
#include "ExampleCameraController.h"
#include "freeglut.h"

ExampleCameraController::ExampleCameraController()
{
    moveSpeed_ = 1.f;
    rotationSpeed_ = glm::radians(10.f);
}

ExampleCameraController::~ExampleCameraController()
{
}

void ExampleCameraController::setCamera(Camera *camera)
{
    camera_ = camera;
}

void ExampleCameraController::keyboardInput(unsigned char key, int x, int y)
{
    glm::vec3 offset(0, 0, 0);
    float yaw = 0;

    switch (key)
    {
    case 'w': offset.z +=  moveSpeed_; break;
    case 's': offset.z -=  moveSpeed_; break;
    case 'd': offset.x += moveSpeed_; break;
    case 'a': offset.x -= moveSpeed_; break;
    case 'q': yaw += rotationSpeed_; break;
    case 'e': yaw -= rotationSpeed_; break;
    }

    if (offset != glm::vec3(0,0,0)) translate(offset);
    if (yaw != 0) rotate(glm::angleAxis(yaw, glm::vec3(0, 1, 0)));
}

void ExampleCameraController::mouseInput(int button, int state, int x, int y)
{
    if (!camera_) return;

    if (lastX_ < 0 || state == GLUT_DOWN) {
        lastX_ = x, lastY_ = y;
    }
    if (x == lastX_ && y == lastY_) return;

    float scale = 0.05f;
    float angy = -(x - lastX_) * rotationSpeed_ * scale;
    float angx = -(y - lastY_) * rotationSpeed_ * scale;
    glm::quat rotx = glm::angleAxis(angx, camera_->getSide());
    glm::quat roty = glm::angleAxis(angy, camera_->getUp());
    rotate(roty * rotx);
    lastX_ = x;
    lastY_ = y;
}

void ExampleCameraController::translate(glm::vec3 const & offset)
{
    if (!camera_) return;

    glm::vec3 pos = camera_->getPosition()
        + camera_->getSide() * offset.x
        + camera_->getDirection() * offset.z
        + camera_->getUp() * offset.y;

    camera_->setViewProperties(pos, camera_->getDirection(), camera_->getSide());
}

void ExampleCameraController::rotate(glm::quat const & rotation)
{
    if (!camera_) return;

    glm::vec3 dir = rotation * camera_->getDirection();
    glm::vec3 side = glm::cross(dir, glm::vec3(0,1,0));
    camera_->setViewProperties(camera_->getPosition(), dir, side);
}
