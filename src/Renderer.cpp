#include "Renderer.h"

#include <iostream>

void GLClearError() {
  while (glGetError() != GL_NO_ERROR);
}

void GLCheckError() {
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL error]: 0x" << std::hex << error << std::endl;
  }
}

bool GLLogcall(const char* func, const char* file, int line) {
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL error]: 0x" << std::hex << error << std::dec << std::endl;
    std::cout << file <<", " << func << ", " << line << std::endl;
    return false;
  }
  return true;
}