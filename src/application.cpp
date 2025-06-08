// Inlcude precompiled header first
#include "pch/pch.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <iostream>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

static const std::string SHADERS_PATH = {"src/res/shaders/Basic.shader"};
static const std::string SEC2_TEXTURE_PATH = {"src/res/textures/SeC2.png"};
static const std::string CHERNO_LOGO_PATH = {"src/res/textures/cherno_logo.png"};

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

  /* Square using index buffer */
  float position_data[] = {
    // Each vertex is a vertices
    100.0f, 100.0f, 0.0f, 0.0f, // idx 0: vertices position and texture coordinate
    200.0f, 100.0f, 1.0f, 0.0f,  // idx 1
    200.0f, 200.0f, 1.0f, 1.0f,   // idx 2
    100.0f, 200.0f, 0.0f, 1.0f,  // idx 3
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3 ,0,
  };

  /**
   * Documentation: https://docs.gl/
   */

  /* Enable blending 
   * Blending: rendering something which is partially or fully transparent.
   * Determines how we combine our output color with what is already in our target buffer (see readme)
   */
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));

  VertexArray va;
  VertexBuffer vb{position_data, sizeof(position_data)};
  VertexBufferLayout layout;

  layout.Push<float>(2);  // How many coordinates per vertex
  layout.Push<float>(2);  // How many coordinates per vertices Texture
  va.AddBuffer(vb, layout);

  IndexBuffer ib{indices, sizeof(indices)/sizeof(indices[0])};  // This must be called after bind the vertex array

  glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f);  // These are the bounds
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
  glm::mat4 mvp = proj * view * model;

  Shader shader(SHADERS_PATH);
  shader.Bind();
  shader.SetUniform4f("u_Color", 0.2f, 0.3f, 1.0f, 1.0f);
  shader.SetUniformMat4f("u_MVP", mvp);

  Texture texture(CHERNO_LOGO_PATH);
  texture.Bind();
  shader.SetUniform1i("u_Texture", 0);

  /* Unbind all */
  va.Unbind();
  vb.Unbind();
  ib.Unbind();
  shader.Unbind();

  /** Pipeline
   * ---------
   * Draw call
   * Vertex shader: is call once per vertex. We tell where that vertex to be.
   * Fragment (pixel) shader: runs one per each pixel. Determines the color for each pixel.
   * Visualisation
   */

  Renderer renderer;

  ImGui::CreateContext();
  ImGui_ImplGlfwGL3_Init(window, true);
  ImGui::StyleColorsDark();

  float r = 0.0f;
  float inc = 0.025f;

  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    renderer.Clear();

    ImGui_ImplGlfwGL3_NewFrame();

    shader.Bind();
    shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

    renderer.Draw(va, ib, shader);

    // Red color increment
    inc = (r > 1.0f) ? -0.01f : (r < 0) ? 0.01f : inc;
    r += inc; 

    {
      static float f = 0.0f;
      static int counter = 0;
      ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
      ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

      ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
      ImGui::Checkbox("Another Window", &show_another_window);

      if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
          counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  ImGui_ImplGlfwGL3_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
  return 0;
}