#include "LineRenderer.h"

static GLuint VAO;
static GLuint VBO;
static GLuint EBO;

static GLuint shaderID;

void InitLineRendering()
{
	const char* vShaderCode =
	"#version 330 core\n"
	"layout(location = 0) in vec2 aPos;\n"
	"\n"
	"uniform mat4 projection;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	vec4 result = projection * vec4(aPos.x, aPos.y, 0.0f, 1.0);\n"
	"	gl_Position = result;\n"
	"}";

	const char * fShaderCode =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"\n"
	"uniform vec4 color;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0,1.0,1.0,1.0);\n"
	"}";

	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
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


	//float accuracy = 10.0f;
	//
	//std::vector<glm::vec2> vertices;
	//vertices.reserve(20 * accuracy);
	//accuracy = 1 / accuracy;
	//
	//float value = -10;
	//int i = 0;
	//
	//while (value <= 10)
	//{
	//	vertices.emplace_back(value, evaluate(value));
	//
	//	i++;
	//	value += accuracy;
	//}
	//m_VertexArray.init();
	//VertexBufferLayout layout;
	//layout.Push<float>(2);
	//
	//std::vector<unsigned short> indecies;
	//indecies.reserve(vertices.size() * 2 + 10);
	//for (size_t i = 0; i < vertices.size(); i++)
	//{
	//	if (i != vertices.size() - 1) {
	//		indecies.push_back(i);
	//		indecies.push_back(i + 1);
	//	}
	//}
	//
	//m_VertexBuffer.init(sizeof(vec2f) * vertices.size(), vertices.data());
	//m_VertexBuffer.Bind();
	//m_VertexArray.AddBuffer(m_VertexBuffer, layout);
	//m_VertexArray.Bind();
	//m_IndexBuffer.Init(sizeof(unsigned short) * indecies.size(), indecies.data());
	//m_VertexArray.Unbind();


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
