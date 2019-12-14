#pragma once
#include "InputController.h"
#include "glm.hpp"
#include "Terrain.h"

//exemplary class that presents how to use input controller to control object
class BallController : public InputController
{
public:
    BallController(Terrain* t);
    virtual ~BallController();

    void keyboardInput(unsigned char key, int x, int y);
    void mouseInput(int button, int state, int x, int y) {}

    glm::vec3 getPos() const;

private:
    Terrain* terrain_;
    float x_ = 0, z_ = 0;
};

