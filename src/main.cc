#include <glad/glad.h>

#include <iostream>

#include "consts.hh"
#include "reader.hh"
#include "window.hh"

// glfw: when window size changed this callback function executes //
// glfwSetFramebufferSizeCallback
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // glfw: the viewport matches the new window dimensions
  glViewport(0, 0, width, height);
}

int main(void) {
  char *vertexShaderSource = readShaderSource("shaders/shader.vert");
  char *fragmentShaderSource = readShaderSource("shaders/shader.frag");

  GLFWwindow *window;

  if (int x = init()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return x;
  }

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
  if (!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  /* Glad loads all OpenGL function pointers */
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << "\n";
    return -1;
  }

  /* Build and compile shader program */
  int success;
  char errorInfo[512];

  /* Vertex shader */
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, errorInfo);
    std::cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n"
              << errorInfo << "\n";
    return -1;
  }

  /* Fragment shader */
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, errorInfo);
    std::cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n"
              << errorInfo << "\n";
    return -1;
  }

  /* Link shaders */
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, errorInfo);
    std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << errorInfo << "\n";
    return -1;
  }

  /* Delete shaders after linking */
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float currentVertices[BUFFER_SIZE];
  for (int i = 0; i < BUFFER_SIZE; i++) {
    currentVertices[i] = initialVertices[i];
  }

  unsigned int indices[] = {
      7, 1, 0,  // first triangle
      1, 0, 13  // second triangle
  };

  // set vertex buffer object anb vertex array object and element buffer objects
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // unsigned movableIndices[] = {7, 8, 12, 13};

  PressState pressState = STATIC;

  WLoopStatic staticData = {initialVertices, window};

  WLoopState state = {currentVertices, &pressState};

  WLoopData data = {staticData, state};

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    // set vertex buffer object anb vertex array object and element buffer

    // bind vertex array object
    glBindVertexArray(VAO);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(initialVertices),
                 data.state.currentVertices, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // unbind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    windowLoop(shaderProgram, VAO, data);
  }

  /* De-allocate all resources */
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return 0;
}
