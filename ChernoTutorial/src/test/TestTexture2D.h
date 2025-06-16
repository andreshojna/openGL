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

static const std::string SHADERS_PATH = {"src/res/shaders/Basic.shader"};
static const std::string CHERNO_LOGO_PATH = {"src/res/textures/cherno_logo.png"};

class TestTexture2D : public Test {
public:
  TestTexture2D();
  ~TestTexture2D();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;

private:
 std::unique_ptr<VertexArray> m_VAO;
 std::unique_ptr<IndexBuffer> m_IndexBuffer;
 std::unique_ptr<Shader> m_Shader;
 std::unique_ptr<Texture> m_Texture;

 glm::vec3 m_TranslationA, m_TranslationB;
 glm::mat4 m_Projection, m_View;
};

} // namespace Test