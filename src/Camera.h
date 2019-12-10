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
#include "glew.h"
#include "glm.hpp"
#include "ext.hpp"

/*exemplary implementation of Camera based on quaterions source of camera and perspective matrix*/
class Camera
{
public:
    Camera();
    virtual ~Camera();

    // set view properties
    // rotation is described by direction and side
    void setViewProperties(
        glm::vec3 const& position,
        glm::vec3 const& direction,
        glm::vec3 const& side);

    // set view properties
    // rotation is described by quaternion
    void setViewProperties(
        glm::vec3 const& position,
        glm::quat const& rotation);

    // set projection properties
    void setProjectionProperties(
        float fovy,
        float znear,
        float zfar);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    glm::vec3 getPosition() const { return pos_; }
    glm::vec3 getDirection() const { return dir_; }
    glm::vec3 getSide() const { return side_; }
    glm::vec3 getUp() const { return glm::cross(side_, dir_); }

    float getFovY() const { return fovy_; }
    float getZNear() const { return znear_; }
    float getZFar() const { return zfar_; }

private:
    glm::vec3 pos_, dir_, side_;
    float fovy_, znear_, zfar_;
};

