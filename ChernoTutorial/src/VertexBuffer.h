#pragma once

class VertexBuffer {
public:
  /**
   * @brief Construct a new Vertex Buffer object
   * 
   * @param data Pointer to data that will be copied into the data store for
   * initialization, or NULL if no data is to be copied.
   * @param size Specifies the size in bytes of the buffer object's new data store
   *
   * @note The vertex buffer will be of type GL_STATIC_DRAW.
   */
  VertexBuffer(const void* data, unsigned int size);

  /**
   * @brief Construct a new Vertex Buffer object
   * 
   * @param data Pointer to data that will be copied into the data store for
   * initialization, or NULL if no data is to be copied.
   * @param size Specifies the size in bytes of the buffer object's new data store
   * @param usage_hint Specifies the expected usage pattern of the data store. 
   * The symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, 
   * GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, 
   * or GL_DYNAMIC_COPY. 
   */
  VertexBuffer(const void* data, unsigned int size, unsigned int usage_hint);

  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;

  void SetSubData(const void* data, unsigned int size);

private:
  unsigned int m_RendererId;
};