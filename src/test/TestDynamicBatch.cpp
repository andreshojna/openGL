#include "TestDynamicBatch.h"

#include "imgui/imgui.h"

#include "IndexBufferDynamic.h"

namespace Test {

static const std::string SHADERS_PATH = {"src/res/shaders/BatchTexture.shader"};

TestDynamicBatch::TestDynamicBatch(const std::string& path_tex_1, const std::string& path_tex_2) :
    m_Translation{0.0f, 0.0f, 0.0f}, 
    m_Projection{glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f)},
    m_View{glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))},
    m_PathTexA{path_tex_1}, m_PathTexB{path_tex_2} {

  unsigned int indices[m_MaxIndexCount];
  unsigned int offset = 0;
  for (size_t i = 0; i < m_MaxIndexCount; i += 6 ) {
    indices[i + 0] = 0 + offset;
    indices[i + 1] = 1 + offset;
    indices[i + 2] = 2 + offset;

    indices[i + 3] = 2 + offset;
    indices[i + 4] = 3 + offset;
    indices[i + 5] = 0 + offset;

    offset += 4;
  }

  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));

  m_VAO = std::make_unique<VertexArray>();
  m_VBO = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * m_MaxVertexCount, GL_DYNAMIC_DRAW);
  VertexBufferLayout layout;

  layout.Push<float>(2);  // How many floats per vertex position
  layout.Push<float>(4);  // How many floats per vertex color
  layout.Push<float>(2);  // How many floats per vertex texture
  layout.Push<float>(1);  // How many floats per texture index
  m_VAO->AddBuffer(*m_VBO, layout);

  m_IndexBuffer = std::make_unique<IndexBufferDynamic>(indices, sizeof(indices)/sizeof(indices[0]));  // This must be called after bind the vertex array

  m_Shader = std::make_unique<Shader>(SHADERS_PATH);
  m_Shader->Bind();

  m_TextureA = std::make_unique<Texture>(m_PathTexA);
  m_TextureB = std::make_unique<Texture>(m_PathTexB);

  /* Unbind all */
  m_VAO->Unbind();
  m_VBO->Unbind();
  m_IndexBuffer->Unbind();
  m_Shader->Unbind();
}

TestDynamicBatch::~TestDynamicBatch() {}

Vertex* TestDynamicBatch::CreateQuad(Vertex* target, float x, float y, float textureId) {
  float size = 2.0f;

  target->position = {x, y};
  target->color = {0.18f, 0.6f, 0.96f, 1.0f};
  target->texCoords = {0.0f, 0.0f};
  target->texId = {textureId};
  target++;

  target->position = {x + size, y};
  target->color = {0.18f, 0.6f, 0.96f, 1.0f};
  target->texCoords = {1.0f, 0.0f};
  target->texId = {textureId};
  target++;

  target->position = {x + size, y + size};
  target->color = {0.18f, 0.6f, 0.96f, 1.0f};
  target->texCoords = {1.0f, 1.0f};
  target->texId = {textureId};
  target++;

  target->position = {x, y + size};
  target->color = {0.18f, 0.6f, 0.96f, 1.0f};
  target->texCoords = {0.0f, 1.0f};
  target->texId = {textureId};
  target++;

  return target;
}

void TestDynamicBatch::OnUpdate(float deltaTime) {
  std::array<Vertex, 1000> vertices;
  Vertex* buffer = vertices.data();
  for (int y = 0; y < 5; y += 2) {
    for (int x = 0; x < 5; x += 2) {
      buffer = CreateQuad(buffer, x, y, (x+y)%4 ? 1 : 0);
      m_IndexBuffer->IncreaseUseCount(6);
    }
  }

  buffer = CreateQuad(buffer, m_QuadPosition[0], m_QuadPosition[1], 0.0f);
  m_IndexBuffer->IncreaseUseCount(6);

  /* Set dynamic vertex buffer */
  m_VBO->SetSubData(vertices.data(), sizeof(Vertex) * vertices.size());
}

void TestDynamicBatch::OnRender() {
  GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestDynamicBatch::OnImGuiRender() {
  Renderer renderer;

  {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
    glm::mat4 mvp = m_Projection * m_View * model;
    m_Shader->Bind();
    m_Shader->SetUniformMat4f("u_MVP", mvp);

    m_TextureA->BindTextureUnit(0);
    m_TextureB->BindTextureUnit(1);
    int samplers[2] = {0, 1};
    m_Shader->SetUniform1iv("u_Textures", 2, samplers);

    renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    m_IndexBuffer->ClearUseCount();
  }

  {
    ImGui::DragFloat2("Quad position", m_QuadPosition, 0.1f);
    ImGui::SliderFloat3("translationA", &m_Translation.x, -8.0f, 8.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }
}

} // namespace Test