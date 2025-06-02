#include "VertexArray.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
  GLCall(glGenVertexArrays(1, &m_RenderId));
}

VertexArray::~VertexArray() {
  GLCall(glDeleteVertexArrays(1, &m_RenderId));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
  Bind();
  vb.Bind();
  const auto& elements = layout.GetElemets();
  unsigned int offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++) {
    const auto& element = elements[i];

    /* Set the vertex atributes: that is, explain the layout. Possition, color, normal, texture, all are attributes 
    * This line links the vertex buffer with the array buffer.
    * stride: amount of bytes between vertex: the size of each vertex depends on the defined attributes
    * pointer: index in bytes inside the vertex, its like the offset where the attribute is inside the vertex
    */
    GLCall(glVertexAttribPointer(i,                     // Index:
                                element.count,          // size: number of components per generic vertex attribute. (1 to 4)
                                element.type,           // type
                                element.normalized,     // normalize
                                layout.GetStride(),     // stride: two floats per vertex = 8bytes
                                (const void*) (intptr_t) offset)); // pointer: we only have one attribute per vertex
    GLCall(glEnableVertexAttribArray(i));  // index to the attribute in the vertex
    offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
  }
}

void VertexArray::Bind() const {
  GLCall(glBindVertexArray(m_RenderId));
}

void VertexArray::Unbind() const {
  GLCall(glBindVertexArray(0));
}