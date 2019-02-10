#include "LineRenderer.h"

static GLuint VAO;
static GLuint VBO;
static GLuint EBO;

static GLuint shaderID;

void InitLineRendering()
{
	std::string vShaderCode = ReadEntireTextFile("../../shaders/Line.vert");
	std::string fShaderCode = ReadEntireTextFile("../../shaders/Line.frag");

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

	glUseProgram(0);

	glEnable(GL_LINE_SMOOTH);
}

void RenderLine(std::vector<glm::vec2>& points)
{
	glUseProgram(shaderID);
	glLineWidth(3.0f);
	std::vector<unsigned int> indecies;


	//indecies.push_back(0);
	for (int i = 0; i < points.size(); i++)
	{
		if (i != points.size() - 1) {
			indecies.push_back(i);
			if (i < points.size())
				indecies.push_back(i + 1);
		}
	}

	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * points.size() , points.data() , GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indecies.size() , indecies.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	//glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));

	glDrawElements(GL_LINES, indecies.size(), GL_UNSIGNED_INT, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}
