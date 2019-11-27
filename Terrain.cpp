#include "Terrain.h"
#include "Shader_Loader.h"
#include "Render_Utils.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))



Terrain::Terrain() : RenderObject() {
}
Terrain::~Terrain()
{
}
void Terrain::init() {
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
	if (model.texCoord.size() > 0) {
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

float Terrain::getHeight(float a, float b) {
	//x = -x;
	y = -y;
	//return sin(x / 5.3)*cos(y / 5.12)*0.5 + 40 / ((x - 1)*(x - 1) / 10 + 2) * 1 / ((y - 1)*(y - 1) / 10 + 2) + 30 / ((x - 14)*(x - 14) / 10 + 2) * 1 / ((y - 10)*(y - 10) / 10 + 2) - 30 / ((x - 14)*(x - 14) / 30 + 2) * 1 / ((y + 2)*(y + 2) / 30 + 2);
	return sin(x / 12.3)*cos(y / 13.12) * 3 + 40 / ((x - 5)*(x - 5) / 10 + 2) * 1 / ((y - 5)*(y - 5) / 10 + 2) + 30 / ((x - 14)*(x - 14) / 10 + 2) * 1 / ((y - 10)*(y - 10) / 10 + 2) - 40 / ((x - 14)*(x - 14) / 40 + 2) * 1 / ((y + 15)*(y + 15) / 50 + 2);
}

void Terrain::render(RenderData& data)
{

	glUseProgram(program);	
	glBindVertexArray(vertexArray);
	glm::mat4 mvp = data.cameraProjectionMatrix*getModelMatrix();
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