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

class Shader_Loader
{
private:

    std::string ReadShader(char *filename);
    GLuint CreateShader(GLenum shaderType,
                        std::string source,
                        char* shaderName);

public:

    Shader_Loader(void);
    virtual ~Shader_Loader(void);
    GLuint CreateProgram(char* VertexShaderFilename,
                         char* FragmentShaderFilename);

    void DeleteProgram(GLuint program);

};
}