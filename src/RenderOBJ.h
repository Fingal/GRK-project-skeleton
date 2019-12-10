#pragma once
#include "RenderObject.h"
#include "Render_Utils.h"

//exemplary clas that should be used in your project
//this is simple class that loads obj file and displays normals
typedef glm::mat4(*matrixFunction)(float time);

class RenderOBJ :
    public RenderObject
{
public:
    RenderOBJ(const char* path);
    RenderOBJ(const char* path,RenderObject* parent);

    void setMatrixFunction(glm::mat4(*matrixFunction)(float time));

    glm::mat4 calculateTransformationMarix(float time);


    void render(RenderData& data);

    virtual ~RenderOBJ();


private:
    void init(const char * path);

    obj::Model model;
    int size;

    GLuint program;
    GLuint vertexArray;
    GLuint vertexBuffer;
    GLuint vertexIndexBuffer;
    matrixFunction matrixFunction;
};

