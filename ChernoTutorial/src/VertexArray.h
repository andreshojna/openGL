#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

  void Bind() const;
  void Unbind() const;

private:
  unsigned int m_RenderId;
};