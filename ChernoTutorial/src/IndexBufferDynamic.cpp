#include "IndexBufferDynamic.h"

#include <GL/glew.h>

#include "Renderer.h"

IndexBufferDynamic::IndexBufferDynamic(const unsigned int* data, unsigned int count)
    : IndexBuffer(data, count), m_UseCount{0} {
  ASSERT(sizeof(unsigned int) == sizeof(GLint));

  GLCall(glGenBuffers(1, &m_RendererId));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                      count * sizeof(unsigned int),
                      data,
                      GL_STATIC_DRAW));
}

IndexBufferDynamic::~IndexBufferDynamic() {
}

