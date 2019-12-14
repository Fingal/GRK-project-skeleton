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

#include "glew.h"
#include "freeglut.h"
#include <iostream>

namespace Core
{

class ShaderLoader
{
public:
    ShaderLoader(void);
    virtual ~ShaderLoader(void);
    GLuint CreateProgram(char* VertexShaderFilename,
                         char* FragmentShaderFilename);

    void DeleteProgram(GLuint program);

private:
    std::string ReadShader(char *filename);
    GLuint CreateShader(GLenum shaderType,
                        std::string source,
                        char* shaderName);
};

}