#pragma once

#include <GL/glew.h>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#define ASSERT(x) if (!(x)) __builtin_trap()

#define GLCall(x) GLClearError();   \
  x;                                \
  ASSERT(GLLogcall(#x, __FILE__, __LINE__));

void GLClearError();

void GLCheckError();

bool GLLogcall(const char* func, const char* file, int line);

class Renderer {
public:
  void Clear() const;
  void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
private:
};