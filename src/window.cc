#include "window.hh"

#include <glad/glad.h>

#include <iostream>

#include "consts.hh"

void incr(WLoopData data, int index, bool positive) {
  std::cout << " - " << std::endl
            << data.state.currentVertices[index] << std::endl;
  float increment = (0.5f + data.global.initialVertices[index] -
                     data.state.currentVertices[index]) /
                    50;
  if (positive) {
    data.state.currentVertices[index] += increment;
  } else {
    data.state.currentVertices[index] -= increment;
  }
  std::cout << data.state.currentVertices[index];
}

void processInput(WLoopData data) {
#ifdef TEST

  if (glfwGetKey(data.global.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(data.global.window, true);
  }

  if (glfwGetKey(data.global.window, GLFW_KEY_Q) ==
      GLFW_PRESS) {  // x of top right
    data.state.currentVertices[0] = 1.0f;
  } else {
    data.state.currentVertices[0] = data.global.initialVertices[0];
  }
  if (glfwGetKey(data.global.window, GLFW_KEY_B) ==
      GLFW_PRESS) {  // y of top right
    data.state.currentVertices[1] = 1.0f;
  } else {
    data.state.currentVertices[1] = data.global.initialVertices[1];
  }
  if (glfwGetKey(data.global.window, GLFW_KEY_C) == GLFW_PRESS) {
    data.state.currentVertices[2] = 1.0f;
  } else {
    data.state.currentVertices[2] = data.global.initialVertices[2];
  }
  if (glfwGetKey(data.global.window, GLFW_KEY_D) ==
      GLFW_PRESS) {  // x of bottom right
    data.state.currentVertices[3] = 1.0f;
  } else {
    data.state.currentVertices[3] = data.global.initialVertices[3];
  }
  if (glfwGetKey(data.global.window, GLFW_KEY_E) ==
      GLFW_PRESS) {  // y of bottom right
    data.state.currentVertices[4] = 1.0f;
  } else {
    data.state.currentVertices[4] = data.global.initialVertices[4];
  }
  if (glfwGetKey(data.global.window, GLFW_KEY_F) == GLFW_PRESS) {
    data.state.currentVertices[5] = 1.0f;
  } else {
    data.state.currentVertices[5] = data.global.initialVertices[5];
  }
  if (glfwGetKey(data.global.window, GLFW_KEY_G) ==
      GLFW_PRESS) {  // x of bottom left
    data.state.currentVertices[6] = 1.0f;
  } else {
    data.state.currentVertices[6] = data.global.initialVertices[6];
  }
  if (glfwGetKey(data.global.window, GLFW_KEY_H) ==
      GLFW_PRESS) {  // y of bottom left
    data.state.currentVertices[7] = 1.0f;
  } else {
    data.state.currentVertices[7] = data.global.initialVertices[7];
  }
  if (glfwGetKey(data.global.window, GLFW_KEY_I) == GLFW_PRESS) {
    data.state.currentVertices[8] = 1.0f;
  } else {
    data.state.currentVertices[8] = data.global.initialVertices[8];
  }
  if (glfwGetKey(data.global.window, GLFW_KEY_J) ==
      GLFW_PRESS) {  // x of top left
    data.state.currentVertices[9] = 1.0f;
  } else {
    data.state.currentVertices[9] = data.global.initialVertices[9];
  }
  if (glfwGetKey(data.global.window, GLFW_KEY_K) ==
      GLFW_PRESS) {  // y of top left
    data.state.currentVertices[10] = 1.0f;
  } else {
    data.state.currentVertices[10] = data.global.initialVertices[10];
  }
  if (glfwGetKey(data.global.window, GLFW_KEY_L) == GLFW_PRESS) {
    data.state.currentVertices[11] = 1.0f;
  } else {
    data.state.currentVertices[11] = data.global.initialVertices[11];
  }
#endif

#ifdef BOUNCE
  if (glfwGetKey(data.global.window, GLFW_KEY_ENTER) == GLFW_PRESS &&
      *data.state.pressState == STATIC) {
    *data.state.pressState = UP;
    std::cout << "--- Pressed ---" << std::endl;
  }

  if (*data.state.pressState != STATIC) {
    std::cout << " Rendering ";
    if (*data.state.pressState == UP) {
      if (data.state.currentVertices[7] >
          data.global.initialVertices[7] + 0.45f) {
        *data.state.pressState = DOWN;
        std::cout << " --- Top --- " << std::endl;
      } else {
        for (int i = 0; i < NB_VERTICES; i++) {
          incr(data, 2 * i + 1, true);
        }
      }
    } else {
      if (data.state.currentVertices[7] <
          data.global.initialVertices[7] + 0.05f) {
        std::cout << " --- Bottom --- " << std::endl;
        *data.state.pressState = STATIC;
        for (int i = 0; i < BUFFER_SIZE; i++) {
          data.state.currentVertices[i] = data.global.initialVertices[i];
        }
      } else {
        for (int i = 0; i < 26; i++) {
          incr(data, 2 * i + 1, false);
        }
      }
    }
    std::cout << std::endl;
  }
#endif
}

int init() {
  /* Initialize the library */
  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  return 0;
}

void windowLoop(unsigned int shaderProgram, unsigned int VAO, WLoopData data) {
  processInput(data);

  glClearColor(0.f, 0.f, 0.f, 0.f);
  glClear(GL_COLOR_BUFFER_BIT);

  /* Draw triangle */
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  /* Swap front and back buffers */
  glfwSwapBuffers(data.global.window);

  /* Poll for and process events */
  glfwPollEvents();
}