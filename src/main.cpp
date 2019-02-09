#include <vector>
#include <iostream>
#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "TextRenderer.h"

class BezierCurve {
public:
	void RegisterPoint(float x, float y) {
		points.push_back({ x,y });
	}

	void ClearPoints() {
		points.clear();
	}

	void DebugPoints() {
		for (int p_index = 0; p_index < points.size() ; p_index++)
		{
			glm::vec2& p = points[p_index];
			std::cout << 'p' << p_index << '(' << p.x << ", " << p.y << ')' << std::endl;
		}
		std::cout << std::endl << std::endl << std::endl;
	}

private:
	std::vector<glm::vec2> points;
};

int main ()
{
	GLFWwindow* window;

	if (!glfwInit())
		std::cout << "Error : could not initilize GLFW";
	int width = 1280;
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(width, width * 9/16, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "Error : could not create window";
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cout << "Error : could not initilize Glad";

	BezierCurve curve;

	glfwSwapInterval(1);

	bool mouseHeld = false;

	FT_Library  library;

	auto error = FT_Init_FreeType(&library);
	if (error)
	{
		std::cout << "Error : could not initilize freetype";
	}

	FT_Face face;
	if (FT_New_Face(library, "../../fonts/arial.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	InitTextRendering(face);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.1f, 0.1f, 0.1f, 1);
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwPollEvents();

		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		RenderText("This is sample text", 25.0f, 25.0f, 1.0f, {0.5, 0.8f, 0.2f});
		RenderText("(C) LearnOpenGL.com", 200, 200, 0.5f, {0.3, 0.7f, 0.9f});

		// Swap the buffers
		glfwSwapBuffers(window);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && mouseHeld == false) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			curve.RegisterPoint(xpos, ypos);

			mouseHeld = true;
		}

		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		{
			mouseHeld = true;
		}
		else
		{
			mouseHeld = false;
		}

		if (glfwGetKey(window, GLFW_KEY_X))
			curve.DebugPoints();
	}

	glfwTerminate();
	return 0;

}