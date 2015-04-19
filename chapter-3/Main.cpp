#include "Main.h"
#include "Model.h"
#include "SOff.h"
#include "UserInterface.h"
#include "GLSLProgram.h"

using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
CGLSLProgram * glslProgram;
CUserInterface * userInterface;
vector <CModel *> models;
int picked;
glm::mat4 projection, view;

void updateUserInterface()
{
	if (picked > -1)
		models[picked]->setTranslation(userInterface->getModelTranslation());
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < models.size(); i++)
	{	
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, models[i]->getTranslation());

		glm::mat4 mvp = projection * view * model;

		glslProgram->enable();
			glslProgram->loadUniformMatrix("MVP", GShader::UNIFORM_SIZE_4D, glm::value_ptr(mvp));
			models[i]->display();
		glslProgram->disable();
	}
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	projection = glm::perspective(45.0f, (float)gWidth / (float)gHeight, 1.0f, 1000.0f);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
		}
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(x, y))
		return;
}

void charInput(GLFWwindow* window, static unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (int i = 0; i < models.size(); i++)
		delete models[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "Chapter 3", NULL, NULL);

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
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initGlew()
{
	if (glewInit() != GLEW_OK)
		return false;
	else
	{
		printf("Vendor: %s \n", glGetString(GL_VENDOR));
		printf("Renderer: %s \n", glGetString(GL_RENDERER));
		printf("OpenGL Version: %s \n", glGetString(GL_VERSION));
		printf("GLSL Version: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));

		printf("\n\nShader: Color \n");

		glslProgram = new CGLSLProgram();
		glslProgram->loadFromFile("../shaders/Color.vert");
		glslProgram->loadFromFile("../shaders/Color.frag");
		glslProgram->create();
		glslProgram->loadUniformVariables();
		glslProgram->loadAttributeVariables();

		return true;
	}
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = new CUserInterface();

	return true;
}

bool initScene()
{
	CSOff* soff = new CSOff();
	
	if(!soff->load("../models/cube.soff"))
		return false;
	
	models.push_back(soff);

	return true;
}

int main(void)
{
	gWidth = 1024;
	gHeight = 768;
	picked = 0;

	if (!initGlfw() || !initGlew() || !initScene() || !initUserInterface())
		return EXIT_FAILURE;

	glEnable(GL_DEPTH_TEST);

	reshape(gWindow, gWidth, gHeight);

	view = glm::lookAt(glm::vec3(3.0f, 3.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	while (!glfwWindowShouldClose(gWindow))
	{
		display();

		TwDraw();

		updateUserInterface();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}