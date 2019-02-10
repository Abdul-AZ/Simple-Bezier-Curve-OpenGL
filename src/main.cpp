#include <vector>
#include <iostream>
#include <algorithm>
#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "TextRenderer.h"
#include "CircleRenderer.h"
#include "LineRenderer.h"

int Factorial(int x) {
	if (x > 1)
		return x * Factorial(x - 1);
	else
		return 1;
}

int BinomialCoefficiant(int n, int k) 
{
	return Factorial(n) / (Factorial(k) * Factorial(n - k));
}

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

	std::vector<glm::vec2> GetCurvePoints() {
		std::vector<glm::vec2> curvePoints;

		float curveStart = points[0].x;
		float curveEnd = points[points.size() - 1].x;
		
		float accuracy = 10.0f;
		float currentPoint = curveStart;
		while (currentPoint < curveEnd)
		{
			float t = (currentPoint - curveStart) / (curveEnd - curveStart);

			if (t > 1)
				t = 1;
			if (t < 0)
				t = 0;

			float p0 = points[0].y;
			float p1 = points[1].y;
			float p2 = points[2].y;

			float y = (1 - t) *((1 - t) * p0 + t * p1) + t * ( (1 - t) * p1 + t * p2);

			curvePoints.push_back(glm::vec2(currentPoint, y));
			currentPoint += accuracy;
		}

		return curvePoints;
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
	InitLineRendering();

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

		if (curve.points.size() > 2)
			RenderLine(curve.GetCurvePoints());

		// Swap the buffers
		glfwSwapBuffers(window);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && mouseHeld == false) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);

			if(curve.points.size() < 3)
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