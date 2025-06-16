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

struct Vec2 {
  float x, y;
};

struct Vec4 {
  float x, y, z, w;
};

struct Vertex {
  Vec2 position;
  Vec4 color;
  Vec2 texCoords; 
  float texId;
};

class TestDynamicBatch : public Test {
public:
  TestDynamicBatch(const std::string& path_tex_1, const std::string& path_tex_2);
  ~TestDynamicBatch();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;

private:
  static constexpr size_t m_MaxQuadCount = 1000;
  static constexpr size_t m_MaxVertexCount = m_MaxQuadCount * 4;
  static constexpr size_t m_MaxIndexCount = m_MaxQuadCount * 6;

  std::unique_ptr<VertexArray> m_VAO;
  std::unique_ptr<VertexBuffer> m_VBO;
  std::unique_ptr<IndexBuffer> m_IndexBuffer;
  std::unique_ptr<Shader> m_Shader;
  std::unique_ptr<Texture> m_TextureA, m_TextureB;

  std::string m_PathTexA, m_PathTexB;

  glm::vec3 m_Translation;
  glm::mat4 m_Projection, m_View;

  float m_QuadPosition[2] = {-4.0f, -1.0f};

  Vertex* CreateQuad(Vertex* target, float x, float y, float textureId);
};

} // namespace Test