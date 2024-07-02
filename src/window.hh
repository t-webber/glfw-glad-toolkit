#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int init();

void windowLoop(GLFWwindow *window, unsigned int shaderProgram,
                unsigned int VAO, float vertices[12]);