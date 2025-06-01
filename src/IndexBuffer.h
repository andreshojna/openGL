#pragma once

class IndexBuffer {
public:
  /**
   * @brief Construct a new Index Buffer object
   * 
   * @param data Address to the indeces data array
   * @param count Quantity of indeces in data array
   */
  IndexBuffer(const unsigned int* data, unsigned int count);

  ~IndexBuffer();

  /** Bind the IndexBuffer */
  void Bind() const;

  /** Unbind the index buffer */
  void Unbind() const;

  /**
   * @brief Get the indices quantity
   * 
   * @return unsigned int with indeces quantity
   */
  inline unsigned int GetCount() const { return m_Count; }

private:
  unsigned int m_RendererId;
  unsigned int m_Count;
};