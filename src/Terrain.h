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
#include "Renderable.h"

class Terrain : public Renderable
{
public:
    Terrain() {}
    virtual ~Terrain() {}

    virtual glm::mat4 getModelMatrix() const = 0;
    virtual void update(float time) = 0;
    virtual void render(RenderData& data) = 0;

    // number of grid rows
    // (equals number of grid points along z-axis)
    // (rows are parallel to x-axis)
    virtual int getRows() const = 0;

    // number of grid columns
    // (equals number of grid points along x-axis)
    // (columns are parallel to z-axis)
    virtual int getCols() const = 0;

    // dimension along x-axis
    virtual float getSizeX() const = 0;

    // dimension along z-axis
    virtual float getSizeZ() const = 0;

    // height at position x, z
    virtual float getHeight(float x, float z) const = 0;
};

/*************************************************
Example
**************************************************
Terrain heightfield (4 rows x 5 cols)
('o' are vertices, lines are edges of triangles)

         15m
  o---o---o---o---o
  | / | / | / | / |
  o---o---o---o---o
  | / | / | / | / |  10m
  o---o---o---o---o
  | / | / | / | / |
  o---o---o---o---o

getRows() should return 4
getCols() should return 5
getSizeX() should return 15
getSizeZ() should return 10

getHeight(7.5, 5) should return interpolated
height at the center of the terrain

getHeight(0, 0) should return the height
of the left-bottom vertex

getHeight(15, 0) should return the height
of the right-bottom vertex

**********************************/