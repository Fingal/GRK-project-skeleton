#include "Terrain.h"
#include "Shader_Loader.h"
#include "Render_Utils.h"

#define BUFFER_OFFSET(i) ((char*)nullptr + (i))

Terrain::Terrain() : Renderable()
{
}

Terrain::~Terrain()
{
}

void Terrain::init()
{
    obj::Model model = obj::loadModelFromFile("models/terrain.obj");

    faceCount = model.faces["default"].size();

    Core::Shader_Loader shaderLoader;
    program = shaderLoader.CreateProgram(
        "shaders/shader_terrain.vert",
        "shaders/shader_terrain.frag");

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
    glVertexAttribPointer(glUV, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vsize+nsize));

    glBindVertexArray(0);
}

glm::mat4 Terrain::getModelMatrix() const
{
    return glm::mat4();
}

void Terrain::update(float time)
{
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
        faceCount,    // count
        GL_UNSIGNED_SHORT,   // type
        (void*)0           // element array buffer offset
    );
    glBindVertexArray(0);
    glUseProgram(0);
}

float Terrain::getHeight(float x, float z) const
{
    z = -z;
    return sin(x / 12.3)*cos(z / 13.12) * 3 +
        40 / ((x - 5)*(x - 5) / 10 + 2) * 1 / ((z - 5)*(z - 5) / 10 + 2) +
        30 / ((x - 14)*(x - 14) / 10 + 2) * 1 / ((z - 10)*(z - 10) / 10 + 2) -
        40 / ((x - 14)*(x - 14) / 40 + 2) * 1 / ((z + 15)*(z + 15) / 50 + 2);
}
