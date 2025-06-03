#pragma once

#include <string>
#include<unordered_map>

struct ShaderSourceCode {
  std::string VertexSource;
  std::string FragmentSource;
};

class Shader {
public:
  Shader(const std::string& filename);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  // Set uniforms
  void SetUniform1i(const std::string& name, int val);
  void SetUniform1f(const std::string& name, float val);
  void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
  unsigned int m_RendererId;
  std::string m_FilePath;
  std::unordered_map<std::string, int> m_UniformLocationCache;

  unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
  unsigned int CompileShader(unsigned int type, const std::string& source);
  ShaderSourceCode ParseShader(const std::string& filepath);
  int GetUniformLocation(const std::string& name);
};