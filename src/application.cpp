#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
    -0.5f, -0.5f, 0.0f, 0.0f, // idx 0: vertices position and texture coordinate
    0.5f, -0.5f, 1.0f, 0.0f,  // idx 1
    0.5f, 0.5f, 1.0f, 1.0f,   // idx 2
    -0.5f, 0.5f, 0.0f, 1.0f,  // idx 3
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

  glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f);

  Shader shader(SHADERS_PATH);
  shader.Bind();
  shader.SetUniform4f("u_Color", 0.2f, 0.3f, 1.0f, 1.0f);
  shader.SetUniformMat4f("u_MVP", proj);

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
  float r = 0.0f;
  float inc = 0.025f;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    renderer.Clear();

    shader.Bind();
    shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

    renderer.Draw(va, ib, shader);

    // Red color increment
    inc = (r > 1.0f) ? -0.01f : (r < 0) ? 0.01f : inc;
    r += inc; 

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}