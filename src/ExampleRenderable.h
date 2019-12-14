//==============================================================================================
//==============================================================================================
//
//         EXAMPLE: ANIMATED OBJECT
//
//==============================================================================================
//==============================================================================================
#pragma once
#include "Renderable.h"
#include<functional>

//exemplary clas that should be used in your project
//this is simple class that loads obj file and displays normals
typedef glm::mat4(*matrixFunction)(float time);

class ExampleRenderable : public Renderable
{
public:
    ExampleRenderable(const char* path);
    virtual ~ExampleRenderable();

    // set function to be called to update the model matrix
    void setMatrixFunction(std::function<
        glm::mat4(ExampleRenderable*, float)> func);

    void setModelMatrix(glm::mat4 const& matrix);
    glm::mat4 getModelMatrix() const { return modelMatrix_; }

    void update(float time);
    void render(RenderData& data);

private:
    void init(const char * path);

    int faceCount_;

    glm::mat4 localModelMatrix_, modelMatrix_;

    GLuint program_;
    GLuint vertexArray_;
    GLuint vertexBuffer_;
    GLuint vertexIndexBuffer_;
    std::function<glm::mat4(ExampleRenderable*, float)> matrixFunction_;
};

