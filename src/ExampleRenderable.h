//==============================================================================================
//==============================================================================================
//
//         EXAMPLE: ANIMATED OBJECT
//
//==============================================================================================
//==============================================================================================
#pragma once
#include "Renderable.h"
#include "Render_Utils.h"
#include<functional>

//exemplary clas that should be used in your project
//this is simple class that loads obj file and displays normals
typedef glm::mat4(*matrixFunction)(float time);

class ExampleRenderable : public Renderable
{
public:
    ExampleRenderable(const char* path);
    virtual ~ExampleRenderable();

    void setMatrixFunction(std::function<glm::mat4(float)> matrixFunction);

    glm::mat4 getModelMatrix() const { return modelMatrix; }

    void update(float time);
    void render(RenderData& data);

private:
    void init(const char * path);

    int faceCount;

    glm::mat4 modelMatrix;

    GLuint program;
    GLuint vertexArray;
    GLuint vertexBuffer;
    GLuint vertexIndexBuffer;
    std::function<glm::mat4(float)> matrixFunction;
};

