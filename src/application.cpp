#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

static const std::string SHADERS_PATH = {"src/res/shaders/Basic.shader"};

struct ShaderSourceCode {
  std::string VertexSource;
  std::string FragmentSource;
};

static unsigned int CompileShader(unsigned int type, const std::string& source) {
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  // Error handling
  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*) alloca(length * sizeof(char)); // Alloc dynamically in stack
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(id);
    return 0;
  }

  return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
  unsigned int program = glCreateProgram();

  /* Compile shaders */
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  /* Attch shaders to the program */
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  /* Delete intermediates */
  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

static ShaderSourceCode ParseShader(const std::string& pathFile) {
  enum class ShaderType {
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1,
  };
  
  std::ifstream stream(pathFile);
  ShaderType type = ShaderType::NONE;
  std::string line;
  std::stringstream ss[2];

  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        type = ShaderType::VERTEX;

      } else if (line.find("fragment") != std::string::npos) {
        type = ShaderType::FRAGMENT;
      }
    } else {
      if (line[0] == '/') continue;
      ss[(int)type] << line << '\n';
    }
  }
  return { ss[0].str(), ss[1].str() };
}

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
  float position[] = {
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
              sizeof(position),  // size in bytes
              position,          // data address
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

  // ShaderSourceCode source = ParseShader("src/res/shaders/Basic.shader");
  ShaderSourceCode source = ParseShader(SHADERS_PATH);

  unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
  glUseProgram(shader);

  /** Pipeline
   * ---------
   * Draw call
   * Vertex shader: is call once per vertex. We tell where that vertex to be.
   * Fragment (pixel) shader: runs one per each pixel. Determines the color for each pixel.
   * Visualisation
   */

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

  glDeleteProgram(shader);

  glfwTerminate();
  return 0;
}