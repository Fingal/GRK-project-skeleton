#pragma once
#include "RenderObject.h"
/*Terrain object responsible from showing terrain and giving height*/
class Terrain :
    public RenderObject
{
public:
    Terrain();
    ~Terrain();
    glm::mat4 calculateTransformationMarix(float time);

    //returns height at current possition a,b
    float getHeight(float a, float b);

    void render(RenderData& data);

    void init();

private:


    int size;

    GLuint program;
    GLuint vertexArray;
    GLuint vertexBuffer;
    GLuint vertexIndexBuffer;
};

