#include "TestTexture2D.h"

#include <GL/glew.h>

#include "imgui/imgui.h"

namespace Test {

TestTexture2D::TestTexture2D() :
    m_TranslationA{200.0f, 200.0f, 0}, m_TranslationB{400.0f, 200.0f, 0},
    m_Projection{glm::ortho(0.0f, 960.0f, 0.0f, 540.0f)},
    m_View{glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))} {

  /* Square using index buffer */
  float position_data[] = {
    // Each vertex is a vertices
    -50.0f, -50.0f, 0.0f, 0.0f, // idx 0: vertices position and texture coordinate
    50.0f, -50.0f, 1.0f, 0.0f,  // idx 1
    50.0f, 50.0f, 1.0f, 1.0f,   // idx 2
    -50.0f, 50.0f, 0.0f, 1.0f,  // idx 3
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3 ,0,
  };

  /* Enable blending 
   * Blending: rendering something which is partially or fully transparent.
   * Determines how we combine our output color with what is already in our target buffer (see readme)
   */
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));

  m_VAO = std::make_unique<VertexArray>();
  VertexBuffer vb{position_data, sizeof(position_data)};
  VertexBufferLayout layout;

  layout.Push<float>(2);  // How many coordinates per vertex
  layout.Push<float>(2);  // How many coordinates per vertices Texture
  m_VAO->AddBuffer(vb, layout);

  m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices)/sizeof(indices[0]));  // This must be called after bind the vertex array

  // m_Projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f);  // These are the bounds
  // m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  m_Shader = std::make_unique<Shader>(SHADERS_PATH);
  m_Shader->Bind();
  m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 1.0f, 1.0f);
  m_Texture = std::make_unique<Texture>(CHERNO_LOGO_PATH);
  m_Shader->SetUniform1i("u_Texture", 0);

  /* Unbind all */
  m_VAO->Unbind();
  vb.Unbind();
  m_IndexBuffer->Unbind();
  m_Shader->Unbind();
}

TestTexture2D::~TestTexture2D() {}

void TestTexture2D::OnUpdate(float deltaTime) {}

void TestTexture2D::OnRender() {
  GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestTexture2D::OnImGuiRender() {
  Renderer renderer;
  m_Texture->Bind();

  {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
    glm::mat4 mvp = m_Projection * m_View * model;
    m_Shader->Bind();
    m_Shader->SetUniformMat4f("u_MVP", mvp);
    renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
  }

  /* Second logo */
  {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
    glm::mat4 mvp = m_Projection * m_View * model;
    m_Shader->SetUniformMat4f("u_MVP", mvp);
    renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
  }

  {
    ImGui::SliderFloat3("translationA", &m_TranslationA.x, 0.0f, 860.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat3("translationB", &m_TranslationB.x, 0.0f, 860.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }
}

} // namespace Test {