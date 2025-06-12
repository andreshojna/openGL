// Inlcude precompiled header first
#include "pch/pch.hpp"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include "test/TestBatchColor.h"
#include "test/TestBatchTexture.h"
#include "test/TestClearColor.h"
#include "test/TestTexture2D.h"

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

int main(void) {
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit()) {
    return -1;
  }

  /* Use OpenGL 3.3 CORE profile to create VertexArray manually; in compat mode is created by default */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  /* Make context before call Init */
  if (glewInit() != GLEW_OK) {
    std::cout << "GLEW doesn't init properly" << std::endl;
    return 1;
  }

  std::cout << "Using " << glGetString(GL_VERSION) << std::endl;

  /* Each line is a vertex. In OpenGL, a vertex is the basic unit of geometry. It's a point in space that defines shapes like triangles, lines, and points. */

  /* Geometry of square: it is formed by 2 triangles. All plane figures for openGL are triangles
   *   0.5    _____
   *          |   /|
   *          |  / |
   *          | /  |
   *  -0.5    |/___|
   *       -0.5   0.5
   */

  /* Wasteful way to draw a square: repeated vertices */
  // float position_data[] = {
  //   -0.5f, -0.5f, // Each vertex is a vertices
  //   0.5f, -0.5f,
  //   0.5f, 0.5f,

  //   0.5f, 0.5f,
  //   -0.5f, 0.5f,
  //   -0.5f, -0.5f,
  // };

  /**
   * Documentation: https://docs.gl/
   */

  /* Enable blending 
   * Blending: rendering something which is partially or fully transparent.
   * Determines how we combine our output color with what is already in our target buffer (see readme)
   */
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));

  Renderer renderer;

  ImGui::CreateContext();
  ImGui_ImplGlfwGL3_Init(window, true);
  ImGui::StyleColorsDark();

  Test::Test* currentTest = nullptr;
  Test::TestMenu* testMenu = new Test::TestMenu(currentTest);
  currentTest = testMenu;

  testMenu->RegisterTest<Test::TestClearColor>("Clear color");
  testMenu->RegisterTest<Test::TestTexture2D>("Texture 2D");
  testMenu->RegisterTest<Test::TestBatchColor>("BatchColor");
  testMenu->RegisterTest<Test::TestBatchTexture>("BatchTexture",
      "src/res/textures/cherno_logo.png",
      "src/res/textures/SeC2.png");

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    renderer.Clear();

    ImGui_ImplGlfwGL3_NewFrame();
    if (currentTest != nullptr) {
      currentTest->OnUpdate(0.0f);
      currentTest->OnRender();
      ImGui::Begin("Test");
      currentTest->OnImGuiRender();
      if (currentTest != testMenu && ImGui::Button("<-")) {
        delete currentTest;
        currentTest = testMenu;
      }
      ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete currentTest;
  if (currentTest != testMenu) {
    delete testMenu;
  }

  ImGui_ImplGlfwGL3_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
  return 0;
}