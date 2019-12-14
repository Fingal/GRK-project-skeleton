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
    //auto loader = objl::Loader();
    //loader.LoadFile(path);
    model = obj::loadModelFromFile(path);

    //&model->vertex[0]
    //&model->texCoord[0]
    //&model->vertex[0]

    Core::Shader_Loader shaderLoader;
    program = shaderLoader.CreateProgram("shaders/shader_test.vert", "shaders/shader_test.frag");
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glGenBuffers(1, &vertexIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.faces["default"].size() * sizeof(unsigned short), &model.faces["default"][0], GL_STATIC_DRAW);


    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    int buffer_size = model.vertex.size() * sizeof(float) + model.normal.size() * sizeof(float) + model.texCoord.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, model.vertex.size() * sizeof(float), &model.vertex[0]);
    glBufferSubData(GL_ARRAY_BUFFER, model.vertex.size() * sizeof(float), model.normal.size() * sizeof(float), &model.normal[0]);
    model.vertex.size() * sizeof(float) + model.normal.size() * sizeof(float), model.texCoord.size() * sizeof(glm::vec2);
    if (model.texCoord.size() > 0)
    {
        glBufferSubData(GL_ARRAY_BUFFER, model.vertex.size() * sizeof(float) + model.normal.size() * sizeof(float), model.texCoord.size() * sizeof(float), &model.texCoord[0]);
    }
    int vertexSize = model.vertex.size();
    int normalSize = model.normal.size();
    auto glPos = glGetAttribLocation(program, "vertexPosition");
    glEnableVertexAttribArray(glPos);
    glVertexAttribPointer(glPos, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    auto glNor = glGetAttribLocation(program, "vertexNormal");
    glEnableVertexAttribArray(glNor);
    glVertexAttribPointer(glNor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexSize * sizeof(float)));

    auto glUV = glGetAttribLocation(program, "vertexTexCoord");
    glEnableVertexAttribArray(glUV);
    glVertexAttribPointer(glUV, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertexSize * sizeof(float) + normalSize * sizeof(float)));
    glBindVertexArray(0);
    size = model.faces["default"].size();
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
        size,    // count
        GL_UNSIGNED_SHORT,   // type
        (void*)0           // element array buffer offset
    );
    glBindVertexArray(0);
    glUseProgram(0);
}

ExampleRenderable::~ExampleRenderable()
{
}
