//==============================================================================================
//==============================================================================================
//
//         EXAMPLE: ANIMATED OBJECT
//
//==============================================================================================
//==============================================================================================
#include "ExampleRenderable.h"
#include "Shader_Loader.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

ExampleRenderable::ExampleRenderable(const char * path)
{
    init(path);
}

void ExampleRenderable::init(const char * path)
{
    obj::Model model = obj::loadModelFromFile(path);
    faceCount = model.faces["default"].size();

    Core::Shader_Loader shaderLoader;
    program = shaderLoader.CreateProgram(
        "shaders/shader_test.vert",
        "shaders/shader_test.frag");

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glGenBuffers(1, &vertexIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        faceCount * sizeof(unsigned short),
        model.faces["default"].data(), GL_STATIC_DRAW);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    size_t vsize = model.vertex.size() * sizeof(float);
    size_t nsize = model.normal.size() * sizeof(float);
    size_t tsize = model.texCoord.size() * sizeof(float);
    size_t bufsize = vsize + nsize + tsize;
    glBufferData(GL_ARRAY_BUFFER, bufsize, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, model.vertex.data());
    glBufferSubData(GL_ARRAY_BUFFER, vsize, nsize, model.normal.data());
    if (tsize > 0) {
        glBufferSubData(GL_ARRAY_BUFFER, vsize + nsize, tsize, model.texCoord.data());
    }

    auto glPos = glGetAttribLocation(program, "vertexPosition");
    glEnableVertexAttribArray(glPos);
    glVertexAttribPointer(glPos, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    auto glNor = glGetAttribLocation(program, "vertexNormal");
    glEnableVertexAttribArray(glNor);
    glVertexAttribPointer(glNor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vsize));

    auto glUV = glGetAttribLocation(program, "vertexTexCoord");
    glEnableVertexAttribArray(glUV);
    glVertexAttribPointer(glUV, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vsize + nsize));

    glBindVertexArray(0);
}

void ExampleRenderable::setMatrixFunction(std::function<glm::mat4(float)> func)
{
    matrixFunction = func;
}

void ExampleRenderable::update(float time)
{
    if (matrixFunction) {
        modelMatrix = matrixFunction(time);
    }
}

void ExampleRenderable::render(RenderData& data)
{
    glUseProgram(program);
    glBindVertexArray(vertexArray);
    glm::mat4 mvp = data.viewProjMatrix * getModelMatrix();
    glm::mat4 model = getModelMatrix();
    glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&mvp);
    glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&model);
    glUniform3f(glGetUniformLocation(program, "lightSource"), data.lightSource.x, data.lightSource.y, data.lightSource.z);
    glDrawElements(
        GL_TRIANGLES,      // mode
        faceCount,    // count
        GL_UNSIGNED_SHORT,   // type
        (void*)0           // element array buffer offset
    );
    glBindVertexArray(0);
    glUseProgram(0);
}

ExampleRenderable::~ExampleRenderable()
{
}
