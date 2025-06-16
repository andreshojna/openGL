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

void Renderer::Clear() const {
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
  shader.Bind();
  va.Bind();
  ib.Bind();

  //  The drawn buffer will be the last bonded (glBindBuffer)
    GLCall(glDrawElements(GL_TRIANGLES,     // Kind of primitive to render
                          ib.GetCount(),    // Number of indices drawn
                          GL_UNSIGNED_INT,  // Indices type
                          nullptr));        // Offset of the first index in the array in the data store of the buffer currently bound to the GL_ELEMENT_ARRAY_BUFFER target.
}