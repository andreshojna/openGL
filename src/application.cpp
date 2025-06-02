#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

static const std::string SHADERS_PATH = {"src/res/shaders/Basic.shader"};

int main(void) {
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit()) {
    return -1;
  }

  /* Use OpenGL 3.3 CORE profile to create VertexArray manually; in compat mode is created by defualt */
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

  /* Wasteful way to draw a square: repeted vertices */
  // float position_data[] = {
  //   -0.5f, -0.5f, // Each vertex is a vertice
  //   0.5f, -0.5f,
  //   0.5f, 0.5f,

  //   0.5f, 0.5f,
  //   -0.5f, 0.5f,
  //   -0.5f, -0.5f,
  // };

  /* Square using index buffer */
  float position_data[] = {
    // Each vertex is a vertice
    -0.5f, -0.5f, // idx 0
    0.5f, -0.5f,  // idx 1
    0.5f, 0.5f,   // idx 2
    -0.5f, 0.5f,  // idx 3
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3 ,0,
  };

  /**
   * Documentation: https://docs.gl/
   */

  VertexArray va;
  VertexBuffer vb{position_data, sizeof(position_data)};
  VertexBufferLayout layout;

  layout.Push<float>(2);
  va.AddBuffer(vb, layout);

  IndexBuffer ib{indices, sizeof(indices)/sizeof(indices[0])};  // This must be called after bind the vertex array

  Shader shader(SHADERS_PATH);
  shader.Bind();
  shader.SetUniform4f("u_Color", 0.2f, 0.3f, 1.0f, 1.0f);

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

  float r = 0.0f;
  float inc = 0.025f;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    GLClearError();

    shader.Bind();
    shader.SetUniform4f("u_Color", r, 0.3f, 1.0f, 1.0f);

    va.Bind();
    ib.Bind();

    //  The drawn buffer will be the last bonded (glBindBuffer)
    GLCall(glDrawElements(GL_TRIANGLES,     // Kind of primitive to render
                          6,                // Number of indices drawn
                          GL_UNSIGNED_INT,  // Indices type
                          nullptr));        // Offset of the first index in the array in the data store of the buffer currently bound to the GL_ELEMENT_ARRAY_BUFFER target.
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