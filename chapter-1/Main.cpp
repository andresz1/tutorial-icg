#include "Main.h"
#include "Line.h"
#include "Quad.h"

using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
bool gPress;
vector <CFigure *> figures;
FigureType figureSelected;

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < figures.size(); i++)
		figures[i]->display();
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, gWidth, 0.0f, gHeight, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;

			case GLFW_KEY_L:
				figureSelected = LINE;
				break;

			case GLFW_KEY_Q:
				figureSelected = QUAD;
				break;
		}
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	double x, y;
	glfwGetCursorPos(gWindow, &x, &y);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !gPress)
	{
		float ay = gHeight - y;

		if (figureSelected == LINE)
		{
			CLine *line = new CLine();
			line->setVertex(0, x, ay);
			line->setVertex(1, x, ay);
			figures.push_back(line);
		}
		else if (figureSelected == QUAD)
		{
			CQuad *quad = new CQuad();
			quad->setVertex(0, x, ay);
			quad->setVertex(1, x, ay);
			figures.push_back(quad);
		}

		gPress = true;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		gPress = false;
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (gPress)
		figures.back()->setVertex(1, x, gHeight - y);
}

void destroy()
{
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "Simple example", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	
	return true;
}

int main(void)
{
	gWidth = 1024;
	gHeight = 768;
	gPress = false;
	figureSelected = LINE;

	if (!initGlfw())
		return EXIT_FAILURE;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	reshape(gWindow, gWidth, gHeight);

	while (!glfwWindowShouldClose(gWindow))
	{
		display();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}
	
	destroy();

	return EXIT_SUCCESS;
}

