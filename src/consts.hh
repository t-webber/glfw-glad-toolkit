#define BOUNCE
// #define TEST

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const unsigned int NB_VERTICES = 26;
const unsigned int BUFFER_SIZE = NB_VERTICES * 3;

const float initialVertices[BUFFER_SIZE] = {
    // x // y // z
    -1.f,  -1.f,  0.f,  // 0
    -1.f,  -0.5f, 0.f,  // 1
    -1.f,  0.f,   0.f,  // 2
    -1.f,  0.5f,  0.f,  // 3
    -1.f,  1.f,   0.f,  // 4
    -0.5f, -1.f,  0.f,  // 5
    -0.5f, -0.5f, 0.f,  // 7
    -0.5f, 0.f,   0.f,  // 8
    -0.5f, 0.5f,  0.f,  // 9
    -0.5f, 1.f,   0.f,  // 10
    0.f,   -1.f,  0.f,  // 11
    0.f,   -0.5f, 0.f,  // 12
    0.f,   0.f,   0.f,  // 13
    0.f,   0.5f,  0.f,  // 14
    0.f,   1.f,   0.f,  // 15
    0.5f,  -1.f,  0.f,  // 16
    0.5f,  -0.5f, 0.f,  // 17
    0.5f,  0.f,   0.f,  // 18
    0.5f,  0.5f,  0.f,  // 19
    0.5f,  1.f,   0.f,  // 20
    1.f,   -1.f,  0.f,  // 21
    1.f,   -0.5f, 0.f,  // 22
    1.f,   0.f,   0.f,  // 23
    1.f,   0.5f,  0.f,  // 24
    1.f,   1.f,   0.f,  // 25
};