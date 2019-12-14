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

/*abstract class for input controller serves as an interface for them*/
class InputController
{
public:
    InputController() {}
    virtual ~InputController() {}
    virtual void keyboardInput(unsigned char key, int x, int y) = 0;
    virtual void mouseInput(int button, int state, int x, int y) = 0;
};

