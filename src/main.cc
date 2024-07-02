#include <glad/glad.h>

#include <iostream>

#include "reader.hh"
#include "window.hh"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
  }

  /* Delete shaders after linking */
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  /* Set vertex data and index buffer */
  float vertices[] = {
      0.5f,  0.5f,  0.0f,  // top right // 0
      0.5f,  -0.5f, 0.0f,  // bottom right // 1
      -0.5f, -0.5f, 0.0f,  // bottom left // 2
      -0.5f, 0.5f,  0.0f   // top left  // 3
  };

  unsigned int indices[] = {
      0, 1, 2,  // first triangle
      2, 1, 0   // second triangle
  };

  // set vertex buffer object anb vertex array object and element buffer objects
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // bind vertex array object
  glBindVertexArray(VAO);

  // bind vertex buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // bind element buffer objects
  // EBO is stored in the VAO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // registered VBO as the vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // unbind the VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    windowLoop(window, shaderProgram, VAO, vertices);
  }

  /* De-allocate all resources */
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return 0;
}
