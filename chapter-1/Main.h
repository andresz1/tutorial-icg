#include "../headers/glfw3.h"
#include <iostream>
#include <string>
#include <vector>

void display();

void reshape(GLFWwindow *window, int width, int height);

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods);

void mouseButton(GLFWwindow* window, int button, int action, int mods);

void cursorPos(GLFWwindow* window, double x, double y);

void destroy();

bool initGlfw();

int main(void);