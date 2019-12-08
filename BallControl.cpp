#include "BallControl.h"



BallControl::BallControl(Terrain* t)
{
    terrain = t;
    x = 0;
    y = 0;
}

void BallControl::keyboardInput(unsigned char key, int x, int y)
{
    float moveSpeed = 0.1;
    switch (key)
    {
    case 'l':
        this->x += moveSpeed;
        break;
    case 'j':
        this->x -= moveSpeed;
        break;
    case 'k':
        this->y += moveSpeed;
        break;
    case 'i':
        this->y -= moveSpeed;
        break;
    }
}





glm::vec3 BallControl::get_pos()
{
    return glm::vec3(x,terrain->getHeight(x,y),y);
}

BallControl::~BallControl()
{
}
