//==============================================================================================
//==============================================================================================
//
//         EXAMPLE: TERRAIN
//
//==============================================================================================
//==============================================================================================
#pragma once
#include "Renderable.h"

class Terrain : public Renderable
{
public:
    Terrain();
    virtual ~Terrain();

    void init();
    
    glm::mat4 getModelMatrix() const;
    void update(float time);
    void render(RenderData& data);

    //returns height at current position x,z
    float getHeight(float x, float z) const;

private:
    int faceCount_;

    GLuint program_;
    GLuint vertexArray_;
    GLuint vertexBuffer_;
    GLuint vertexIndexBuffer_;
};

