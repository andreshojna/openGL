#pragma once

class IndexBuffer {
public:
  /**
   * @brief Construct a new Index Buffer object
   * 
   * @param data Address to the indices data array
   * @param count Quantity of indices in data array
   */
  IndexBuffer(const unsigned int* data, unsigned int count);

  virtual ~IndexBuffer();

  /** Bind the IndexBuffer */
  virtual void Bind() const;

  /** Unbind the index buffer */
  virtual void Unbind() const;

  /**
   * @brief Get the indices quantity
   * 
   * @return unsigned int with indices quantity
   */
  virtual inline unsigned int GetCount() const { return m_Count; }

  virtual void IncreaseUseCount(unsigned int count) {}

  virtual inline void ClearUseCount() {}

protected:
  unsigned int m_RendererId;
  unsigned int m_Count;
};