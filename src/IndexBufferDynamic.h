#pragma once

#include "IndexBuffer.h"

class IndexBufferDynamic : public IndexBuffer {
public:
  /**
   * @brief Construct a new Index Buffer object
   * 
   * @param data Address to the indices data array
   * @param count Quantity of indices in data array
   */
  IndexBufferDynamic(const unsigned int* data, unsigned int count);

  ~IndexBufferDynamic();

  /**
   * @brief Get the indices quantity
   * 
   * @return unsigned int with indices quantity
   */
  inline unsigned int GetCount() const { return m_UseCount; }

  inline void ClearUseCount() override { m_UseCount = 0; }

  inline void IncreaseUseCount(unsigned int count) override { m_UseCount += count; }

private:
  unsigned int m_UseCount;
};