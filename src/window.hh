
#include <glad/glad.h>
//
#include <GLFW/glfw3.h>

int init();

enum PressState { UP, DOWN, STATIC };

typedef struct WLoopStatic {
  const float *initialVertices;
  GLFWwindow *window;
  // unsigned *movableIndices;
} WLoopStatic;

typedef struct WLoopState {
  float *currentVertices;
  PressState *pressState;
} WLoopState;

typedef struct WLoopData {
  WLoopStatic global;
  WLoopState state;
} WindowLoopData;

void windowLoop(unsigned int shaderProgram, unsigned int VAO, WLoopData data);