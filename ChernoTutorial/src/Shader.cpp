#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"

Shader::Shader(const std::string& filepath) : m_FilePath{filepath}, m_RendererId{0} {
  /* Generate shaders */
  ShaderSourceCode source = ParseShader(filepath);
  m_RendererId = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
  GLCall(glDeleteProgram(m_RendererId));
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
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

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
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

ShaderSourceCode Shader::ParseShader(const std::string& filepath) {
  enum class ShaderType {
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1,
  };
  
  std::ifstream stream(filepath);
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
      // Skip comments
      if (line[0] == '/') continue;
      ss[(int)type] << line << '\n';
    }
  }
  return { ss[0].str(), ss[1].str() };
}

void Shader::Bind() const {
  GLCall(glUseProgram(m_RendererId));
}

void Shader::Unbind() const {
  GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int val) {
  GLCall(glUniform1i(GetUniformLocation(name), val));
}

void Shader::SetUniform1iv(const std::string& name, const size_t count, int* val) {
  GLCall(glUniform1iv(GetUniformLocation(name), count, val));
}

void Shader::SetUniform1f(const std::string& name, float val) {
  GLCall(glUniform1f(GetUniformLocation(name), val));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
  GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
  GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) {
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
    return m_UniformLocationCache[name];
  }
  GLCall(int location = glGetUniformLocation(m_RendererId, name.c_str()));
  if (location == -1) {
    std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
  }
  m_UniformLocationCache[name] = location;
  return location;
}