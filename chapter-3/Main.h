#define GLFW_INCLUDE_GLU
#include "../headers/glew.h"
#include "../headers/glfw3.h"
#include <vector>

void updateUserInterface();

void display();

void reshape(GLFWwindow *window, int width, int height);

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods);

void mouseButton(GLFWwindow* window, int button, int action, int mods);

void cursorPos(GLFWwindow* window, double x, double y);

void charInput(GLFWwindow* window, static unsigned int scanChar);

void destroy();

bool initGlfw();

bool initUserInterface();

int main(void);