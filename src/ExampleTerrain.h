//==============================================================================================
//==============================================================================================
//
//         EXAMPLE: TERRAIN
//
//==============================================================================================
//==============================================================================================
#pragma once
#include "Terrain.h"

class ExampleTerrain : public Terrain
{
public:
    ExampleTerrain();
    virtual ~ExampleTerrain();

    void init();

    glm::mat4 getModelMatrix() const;
    void update(float time);
    void render(RenderData& data);

    int getRows() const;
    int getCols() const;
    float getSizeX() const;
    float getSizeZ() const;
    float getHeight(float x, float z) const;

private:
    int faceCount_;

    GLuint program_;
    GLuint vertexArray_;
    GLuint vertexBuffer_;
    GLuint vertexIndexBuffer_;
};

