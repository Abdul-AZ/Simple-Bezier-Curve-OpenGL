#include <vector>
#include <iostream>
#include "glad/glad.h"
#include "glfw/glfw3.h"
//TODO
#include <ft2build.h>
#include FT_FREETYPE_H

struct point {
	float x, y;
};

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
			point& p = points[p_index];
			std::cout << 'p' << p_index << '(' << p.x << ", " << p.y << ')' << std::endl;
		}
		std::cout << std::endl << std::endl << std::endl;
	}

private:
	std::vector<point> points;
};

int main ()
{
	GLFWwindow* window;

	if (!glfwInit())
		std::cout << "Error : could not initilize GLFW";

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();

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