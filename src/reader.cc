#include "reader.hh"

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

char *readShaderSource(std::string infilename) {
  std::string code;
  std::ifstream shaderFile(infilename);

  if (!shaderFile.is_open()) {
    std::cout << "Failed to open shader file named" << infilename << std::endl;
    return NULL;
  }

  std::string line;
  while (std::getline(shaderFile, line)) {
    code += line + "\n";
  }

  shaderFile.close();
  char *result = (char *)malloc(code.size() + 1);
  strcpy(result, code.c_str());
  return result;
}