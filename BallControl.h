#pragma once
#include "InputControl.h"
#include "glm.hpp"
#include "Terrain.h"


class BallControl :
	public InputControl
{
public:
	BallControl(Terrain* t);

	void keyboardInput(unsigned char key, int x, int y);


	virtual void mouseInput(int button, int state, int x, int y) {};

	glm::vec3 get_pos();
	~BallControl();
private:
	Terrain* terrain;
	float x;
	float y;
};

