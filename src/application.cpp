#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(void) {
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit()) {
    return -1;
  }

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  /* Make context before call Init */
  if (glewInit() != GLEW_OK) {
    std::cout << "GLEW doesn't init properly" << std::endl;
    return 1;
  }

  std::cout << "Using " << glGetString(GL_VERSION) << std::endl;

  /* Each line is a vertex. In OpenGL, a vertex is the basic unit of geometry. It's a point in space that defines shapes like triangles, lines, and points. */
  float position_data[] = {
    -0.5f, -0.5f, // Each vertex is a vertice
    0.0f, 0.5f,
    0.5f, -0.5f,
  };

  /**
   * Documentation: https://docs.gl/
   */

  /* Define buffer */
  unsigned int buffer;      //  Buffer ID
  glGenBuffers(1, &buffer); //  Create buffer
  glBindBuffer(GL_ARRAY_BUFFER, buffer);  //  Select the buffer

  glBufferData(GL_ARRAY_BUFFER,
              sizeof(position_data),  // size in bytes
              position_data,          // data address
              GL_STATIC_DRAW);        // hint

  /* Set the vertex atributes: that is, explain the layout. Possition, color, normal, texture, all are attributes */
  // stride: amount of bytes between vertex: the size of each vertex depends on the defined attributes
  // pointer: index in bytes inside the vertex, its like the offset where the attribute is inside the vertex
  glVertexAttribPointer(0,    // Index:
                        2,    // size: number of components per generic vertex attribute. (1 to 4)
                        GL_FLOAT, // type
                        GL_FALSE, // normalize
                        sizeof(float) * 2, // stride: two floats per vertex = 8bytes
                        0);  // pointer: we only have one attribute per vertex

  glEnableVertexAttribArray(0);  // index to the attribute in the vertex


  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3); //  The drawn buffer will be the last bonded (glBindBuffer)

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}