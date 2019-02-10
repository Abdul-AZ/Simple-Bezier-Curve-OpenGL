#include "CircleRenderer.h"

static GLuint VAO;
static GLuint VBO;

static unsigned int shaderID;

static int VertexCountPerCicle = 0;

void InitCircleRendering(int in_vertexCountPerCicle)
{
	VertexCountPerCicle = in_vertexCountPerCicle + 2;

	std::string vShaderCode = ReadEntireTextFile("../../shaders/Circle.vert");
	std::string fShaderCode = ReadEntireTextFile("../../shaders/Circle.frag");

	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	const char* c_vShaderCode = vShaderCode.c_str();
	glShaderSource(vertex, 1, &c_vShaderCode, NULL);
	glCompileShader(vertex);
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* c_fShaderCode = fShaderCode.c_str();
	glShaderSource(fragment, 1, &c_fShaderCode, NULL);
	glCompileShader(fragment);
	// shader Program
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glLinkProgram(shaderID);
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	glUseProgram(shaderID);

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(1000), static_cast<GLfloat>(1000 * 9 / 16), 0.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glm::vec2* vertices = new glm::vec2[VertexCountPerCicle];

	vertices[0].x = 0.0f;
	vertices[0].y = 0.0f;
	float degreesBetweenVertices = 360.0f / (VertexCountPerCicle - 6);

	const float PI = 3.1415f;

	for (size_t i = 1; i < VertexCountPerCicle; i++)
	{
		float angle = i * degreesBetweenVertices;
		vertices[i].x = cos(angle * (PI / 180.0));
		vertices[i].y = sin(angle * (PI / 180.0));
	}

	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * VertexCountPerCicle, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	delete[] vertices;
}

void RenderCircle(glm::vec2 position, float scale)
{
	glBindVertexArray(VAO);
	glUseProgram(shaderID);
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(position.x, position.y, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, scale));
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glDrawArrays(GL_TRIANGLE_FAN, 0, VertexCountPerCicle);
}
