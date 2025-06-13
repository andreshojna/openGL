#include "VertexBuffer.h"

#include <GL/glew.h>

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
  VertexBuffer(data, size, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int usage_hint) {
  GLCall(glGenBuffers(1, &m_RendererId));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
  GLCall(glBufferData(GL_ARRAY_BUFFER,
              size,             // size in bytes
              data,             // data address
              usage_hint)); // hint
}

VertexBuffer::~VertexBuffer() {
  GLCall(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::Bind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::Unbind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::SetSubData(const void* data, unsigned int size) {
  Bind();
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}