#pragma once

#include "Test.h"

#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Test {

class TestBatch : public Test {
public:
  TestBatch();
  ~TestBatch();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;

private:
 std::unique_ptr<VertexArray> m_VAO;
 std::unique_ptr<IndexBuffer> m_IndexBuffer;
 std::unique_ptr<Shader> m_Shader;
 std::unique_ptr<Texture> m_Texture;

 glm::vec3 m_Translation;
 glm::mat4 m_Projection, m_View;
};

} // namespace Test