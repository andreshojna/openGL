#include "TestBatchTexture.h"

#include "imgui/imgui.h"

namespace Test {

static const std::string SHADERS_PATH = {"src/res/shaders/BatchTexture.shader"};

TestBatchTexture::TestBatchTexture(const std::string& path_tex_1, const std::string& path_tex_2) :
    m_Translation{0.0f, 0.0f, 0.0f}, 
    m_Projection{glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f)},
    m_View{glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))},
    m_PathTexA{path_tex_1}, m_PathTexB{path_tex_2} {

  float vertices[] = {
    // Position(2)        // Color(4)         // Texture(2)  /Texture index
    -4.0f, -1.0f, 0.18f,  0.6f, 0.96f, 1.0f,  0.0f, 0.0f,  0.0f,
    -2.0f, -1.0f, 0.18f,  0.6f, 0.96f, 1.0f,  1.0f, 0.0f,  0.0f,
    -2.0f, 1.0f, 0.18f,  0.6f, 0.96f, 1.0f,  1.0f, 1.0f,  0.0f,
    -4.0f, 1.0f, 0.18f,  0.6f, 0.96f, 1.0f,  0.0f, 1.0f,  0.0f,

    4.0f, -1.0f, 1.0f,  0.93f, 0.24f, 1.0f,  0.0f, 0.0f,  1.0f,
    2.0f, -1.0f, 1.0f,  0.93f, 0.24f, 1.0f,  1.0f, 0.0f,  1.0f,
    2.0f, 1.0f, 1.0f,  0.93f, 0.24f, 1.0f,  1.0f, 1.0f,  1.0f,
    4.0f, 1.0f, 1.0f,  0.93f, 0.24f, 1.0f,  0.0f, 1.0f,  1.0f,
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0,

    4, 5, 6,
    6, 7, 4,
  };

  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));

  m_VAO = std::make_unique<VertexArray>();
  VertexBuffer vb{vertices, sizeof(vertices)};
  VertexBufferLayout layout;

  layout.Push<float>(2);  // How many floats per vertex position
  layout.Push<float>(4);  // How many floats per vertex color
  layout.Push<float>(2);  // How many floats per vertex texture
  layout.Push<float>(1);  // How many floats per texture index
  m_VAO->AddBuffer(vb, layout);

  m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices)/sizeof(indices[0]));  // This must be called after bind the vertex array

  m_Shader = std::make_unique<Shader>(SHADERS_PATH);
  m_Shader->Bind();

  m_TextureA = std::make_unique<Texture>(m_PathTexA);
  m_TextureB = std::make_unique<Texture>(m_PathTexB);

  /* Unbind all */
  m_VAO->Unbind();
  vb.Unbind();
  m_IndexBuffer->Unbind();
  m_Shader->Unbind();
}

TestBatchTexture::~TestBatchTexture() {}

void TestBatchTexture::OnUpdate(float deltaTime) {}

void TestBatchTexture::OnRender() {
  GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestBatchTexture::OnImGuiRender() {
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
  }

  {
    ImGui::SliderFloat3("translationA", &m_Translation.x, -8.0f, 8.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }
}

} // namespace Test