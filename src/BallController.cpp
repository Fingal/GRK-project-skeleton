//==============================================================================================
//==============================================================================================
//
//         EXAMPLE: BALL CONTROLLER
//
//==============================================================================================
//==============================================================================================
#include "BallController.h"

BallController::BallController()
{
}

void BallController::setTerrain(Terrain * t)
{
    terrain_ = t;
}

void BallController::keyboardInput(unsigned char key, int x, int y)
{
    float moveSpeed = 0.1;
    switch (key)
    {
    case 'l':
        x_ += moveSpeed;
        break;
    case 'j':
        x_ -= moveSpeed;
        break;
    case 'k':
        z_ += moveSpeed;
        break;
    case 'i':
        z_ -= moveSpeed;
        break;
    }
}

glm::vec3 BallController::getPos() const
{
    float y = 0;
    if (terrain_) y = terrain_->getHeight(x_, z_);
    return glm::vec3(x_, y, z_);
}

BallController::~BallController()
{
}
