#pragma once
#include "Renderable.h"
/*Terrain object responsible from showing terrain and giving height*/
class Terrain : public Renderable
{
public:
    Terrain();
    virtual ~Terrain();

    void init();
    
    glm::mat4 getModelMatrix() const;
    void update(float time);
    void render(RenderData& data);

    //returns height at current possition x,z
    float getHeight(float x, float z) const;

private:
    int faceCount;

    GLuint program;
    GLuint vertexArray;
    GLuint vertexBuffer;
    GLuint vertexIndexBuffer;
};

