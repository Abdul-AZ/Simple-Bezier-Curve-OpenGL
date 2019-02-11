#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
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
	}

	void ClearPoints() {
		points.clear();
	}

	std::vector<glm::vec2> GetCurve() {
		std::vector<glm::vec2> curvePoints;

		float curveStart = points[0].x;

		float curveLength = 0.0f;

		for (int i = 0; i < points.size() - 1; i++)
		{
			curveLength += abs(sqrt(pow(points[i + 1].x - points[i].x, 2) + pow(points[i + 1].y - points[i].y, 2)));
		}
		
		//specifies how many points will be made
		float accuracy = 1.0f;

		float currentPoint = 0.0f;
		float currentCurveLength = 0.0f;

		while (currentPoint < curveLength)
		{
			float t = currentPoint / curveLength;

			int n = points.size() - 1;
			glm::vec2 point(0.0f,0.0f);

			for (int i = 0; i <= n; i++)
			{
				point += (BinomialCoefficiant(n, i) * pow(1 - t, n - i) * pow(t, i))* points[i];
			}

			curvePoints.push_back(point);
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
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(width, width * 9/16, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "Error : could not create window";
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cout << "Error : could not initilize Glad";

	glfwSwapInterval(1);

	bool mouseHeld = false;

	InitTextRendering();
	InitCircleRendering(32);
	InitLineRendering();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	BezierCurve curve;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		RenderText("Press C to clear points", 25, 525, 0.5, glm::vec3(1.0f, 1.0f, 1.0f));

		for (glm::vec2& vec : curve.points) {
			RenderCircle(glm::vec2(vec.x, vec.y), 5);
		}

		for (int i = 0; i < curve.points.size(); i++)
		{
			std::ostringstream xStream;
			xStream << std::fixed;
			xStream << std::setprecision(0);
			xStream << curve.points[i].x;
			std::string xValue = xStream.str();

			std::ostringstream yStream;
			yStream << curve.points[i].y;
			yStream << std::setprecision(0);
			std::string yValue = yStream.str();

			RenderText("p" + std::to_string(i) + " = (" + xValue + ", " + yValue + ")",
						10, 200 - i * 20, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
		}

		if (curve.points.size() > 1)
			RenderLine(curve.GetCurve());
		//if (curve.points.size() > 1)
		//	RenderLine(curve.points);


		glfwSwapBuffers(window);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && mouseHeld == false) {
			if (curve.points.size() < 10){
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				curve.RegisterPoint(xpos, ypos);
			}
			mouseHeld = true;
		}

		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
			mouseHeld = true;
		else
			mouseHeld = false;

		if (glfwGetKey(window, GLFW_KEY_C))
			curve.ClearPoints();
	}

	glfwTerminate();
	return 0;
}