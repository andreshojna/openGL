#pragma once

#include <GL/glew.h>

#include <vector>

#include "Renderer.h"

/**
 * @brief Vertex buffer element
 * Stores information about the layout
 * 
 */
struct VertexBufferElement {
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static unsigned int GetSizeOfType(unsigned int type) {
    switch (type) {
      case GL_FLOAT:
      case GL_UNSIGNED_INT: return 4;
      case GL_UNSIGNED_BYTE: return 1;
      default:
        ASSERT(false);
        return 0;
    }
  }
};

class VertexBufferLayout {
public:
  VertexBufferLayout() {}
  ~VertexBufferLayout() {}

  /**
   * @brief 
   * @param count number of components per generic vertex attribute
   */
  template<typename T>
  void Push(unsigned int count) {
    ASSERT(false);
  }

  /**
   * @brief Get the Elemets object
   * 
   * @return const std::vector<VertexBufferElement> Vector with vertex buffer elements
   */
  inline const std::vector<VertexBufferElement> GetElemets() const { return m_Elements; }

  /**
   * @brief Get the Stride object
   * 
   * @return unsigned int 
   */
  inline unsigned int GetStride() const { return m_Stride; }

private:
  unsigned int m_Stride = 0;;
  std::vector<VertexBufferElement> m_Elements;
};