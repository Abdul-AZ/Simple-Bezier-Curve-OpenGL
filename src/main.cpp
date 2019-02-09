#include <vector>
#include <iostream>
#include <algorithm>
#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "TextRenderer.h"
#include "CircleRenderer.h"

class BezierCurve {
public:
	void RegisterPoint(float x, float y) {
		points.push_back({ x,y });
		std::sort(points.begin(), points.end(), [](glm::vec2 a, glm::vec2 b) {return a.x < b.x; });
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

public:
	std::vector<glm::vec2> points;
};

int main ()
{
	GLFWwindow* window;

	if (!glfwInit())
		std::cout << "Error : could not initilize GLFW";
	int width = 1000;
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
	InitCircleRendering(32);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.1f, 0.1f, 0.1f, 1);
	while (!glfwWindowShouldClose(window))
	{
		// Check and call events
		glfwPollEvents();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//RenderText("Hello", 100, 100, 1, glm::vec3(1.0f, 1.0f, 1.0f));

		for(glm::vec2& vec : curve.points)
			RenderCircle(glm::vec2(vec.x, vec.y), 5);

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

		if (glfwGetKey(window, GLFW_KEY_C))
			curve.ClearPoints();
	}

	glfwTerminate();
	return 0;

}