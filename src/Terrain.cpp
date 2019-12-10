#include "Terrain.h"
#include "Shader_Loader.h"
#include "Render_Utils.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))



Terrain::Terrain() : RenderObject()
{
}
Terrain::~Terrain()
{
}
void Terrain::init()
{
    //auto loader = objl::Loader();
    //loader.LoadFile(path);
    obj::Model model = obj::loadModelFromFile("models/terrain.obj");

    //&model->vertex[0]
    //&model->texCoord[0]
    //&model->vertex[0]

    Core::Shader_Loader shaderLoader;
    program = shaderLoader.CreateProgram("shaders/shader_terrain.vert", "shaders/shader_terrain.frag");
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


glm::mat4 Terrain::calculateTransformationMarix(float time)
{
    graphNode->matrix = glm::mat4(1.0);
    return graphNode->matrix;
}

float Terrain::getHeight(float a, float b)
{
    //a = -a;
    b = -b;
    //return sin(a / 5.3)*cos(b / 5.12)*0.5 + 40 / ((a - 1)*(a - 1) / 10 + 2) * 1 / ((b - 1)*(b - 1) / 10 + 2) + 30 / ((a - 14)*(a - 14) / 10 + 2) * 1 / ((b - 10)*(b - 10) / 10 + 2) - 30 / ((a - 14)*(a - 14) / 30 + 2) * 1 / ((b + 2)*(b + 2) / 30 + 2);
    return sin(a / 12.3)*cos(b / 13.12) * 3 + 40 / ((a - 5)*(a - 5) / 10 + 2) * 1 / ((b - 5)*(b - 5) / 10 + 2) + 30 / ((a - 14)*(a - 14) / 10 + 2) * 1 / ((b - 10)*(b - 10) / 10 + 2) - 40 / ((a - 14)*(a - 14) / 40 + 2) * 1 / ((b + 15)*(b + 15) / 50 + 2);
}

void Terrain::render(RenderData& data)
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