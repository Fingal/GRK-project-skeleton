#pragma once
#include "glew.h"
#include "glm.hpp"
#include "ext.hpp"

/*exemplary implementation of Camera based on quaterions source of camera and perspective matrix*/
class Camera
{
public:
    Camera();
    virtual ~Camera();

    void changeRotation(glm::vec3 rotationChangeXYZ);

    void move(float dir, float side);

    glm::mat4 getCameraProjectionMatix();

    glm::mat4 createPerspectiveMatrix(float fovY, float zNear, float zFar);


    //sets up window size
    void resize(int width, int height);

private:
    int width, height;
    glm::quat rotation;
    glm::quat rotationChange;
    glm::vec3 cameraDir;
    glm::vec3 cameraSide;
    glm::vec3 cameraPos;

    glm::mat4 createCameraMatrix();
};

