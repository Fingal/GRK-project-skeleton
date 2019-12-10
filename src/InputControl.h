#pragma once

/*abstract class for input controller serves as an interface for them*/
class InputControl
{
public:
    InputControl();
    virtual void keyboardInput(unsigned char key, int x, int y) {};
    virtual void mouseInput(int button, int state, int x, int y) {};
    ~InputControl();
};

