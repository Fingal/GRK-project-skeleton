#pragma once
#include "InputControl.h"
#include "Camera.h"
/*implementation for input control that controls given camera*/
class CameraControl :
	public InputControl
{
public:
	CameraControl(Camera* camera);
	void keyboardInput(unsigned char key, int x,int y);
	void mouseInput(int button, int state, int x, int y);
	~CameraControl();
private:
	int lastX;
	int lastY;
	float moveSpeed;
	Camera* camera;
};

