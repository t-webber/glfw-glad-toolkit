#include "window.hh"

#include <glad/glad.h>

void processInput(GLFWwindow *window, float vertices[12]) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
    glClearColor(0.4f, 0.2f, 0.2f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    vertices[0] -= 1;
  } else {
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    vertices[0] += 1;
  }
}

int init() {
  /* Initialize the library */
  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  return 0;
}

void windowLoop(GLFWwindow *window, unsigned int shaderProgram,
                unsigned int VAO, float vertices[12]) {
  processInput(window, vertices);

  /* Draw triangle */
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  /* Swap front and back buffers */
  glfwSwapBuffers(window);

  /* Poll for and process events */
  glfwPollEvents();
}