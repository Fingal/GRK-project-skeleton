#include "Camera.h"



Camera::Camera()
{
    cameraPos = glm::vec3(0, 10, 20);
    rotation = glm::quat(1, 0, 0, 0);
    rotationChange = glm::quat(1, 0, 0, 0);
}


Camera::~Camera()
{
}

void Camera::move(float dir, float side)
{
    cameraPos = cameraPos + dir * cameraDir + side * cameraSide;
}

glm::mat4 Camera::getCameraProjectionMatix()
{
    return createPerspectiveMatrix(glm::radians(60.f), 0.1f, 1000.f)
           * createCameraMatrix();
}

glm::mat4 Camera::createPerspectiveMatrix(float fovY, float zNear, float zFar)
{
    return glm::perspectiveFovRH(fovY, (float)width, (float)height, zNear, zFar);
}

void Camera::changeRotation(glm::vec3 rotationChangeXYZ)
{
    rotationChange = rotationChange+glm::quat(-rotationChangeXYZ*0.003);
}

void Camera::resize(int w, int h)
{
    width = w;
    height = h;
}

glm::mat4 Camera::createCameraMatrix()
{
    rotation = rotationChange * rotation;
    rotation = glm::normalize(rotation);
    cameraDir = glm::inverse(rotation) * glm::vec3(0, 0, -1);
    cameraSide = glm::inverse(rotation) * glm::vec3(1, 0, 0);

    //return createViewMatrixQuat(cameraPos, rotation);
    glm::mat4 cameraTranslation;
    cameraTranslation[3] = glm::vec4(-cameraPos, 1.0f);

    rotationChange = glm::quat(1, 0, 0, 0);
    return glm::mat4_cast(rotation) * cameraTranslation;
}
