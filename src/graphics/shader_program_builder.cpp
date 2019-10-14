#include "graphics/shader_program_builder.h"

#include <gl/glew.h>
#include <algorithm>
#include <iostream>

#include "core/io/file.h"
#include "graphics/shader_program.h"

void ShaderProgramBuilder::AddShader(const std::string& src,
                                     int32_t shader_handle) {
  const char* c_src = src.c_str();
  glShaderSource(shader_handle, 1, &c_src, nullptr);
  glCompileShader(shader_handle);

  int32_t success;
  glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);
  char info[1024];
  if (!success) {
    glGetShaderInfoLog(shader_handle, 1024, nullptr, info);
    std::cout << "Error: " << info << std::endl;
    exit(EXIT_FAILURE);
  }
}

void ShaderProgramBuilder::AddVert(const std::string& src) {
  int32_t shader_handle = glCreateShader(GL_VERTEX_SHADER);
  AddShader(src, shader_handle);
  vert_handles.push_back(shader_handle);
}

void ShaderProgramBuilder::AddFrag(const std::string& src) {
  int32_t shader_handle = glCreateShader(GL_FRAGMENT_SHADER);
  AddShader(src, shader_handle);
  frag_handles.push_back(shader_handle);
}

std::unique_ptr<ShaderProgram> ShaderProgramBuilder::Build() {
  int32_t handle = glCreateProgram();
  AttachShaders(handle);

  glLinkProgram(handle);

  int32_t success;
  glGetProgramiv(handle, GL_LINK_STATUS, &success);
  if (!success) {
    std::cerr << "Error: Linking Shader\n";
    exit(EXIT_FAILURE);
  }
  return std::make_unique<ShaderProgram>(handle);
}

void ShaderProgramBuilder::AddVertFromFile(const std::string& path) {
  AddVertFromFile(File{path});
}
void ShaderProgramBuilder::AddFragFromFile(const std::string& path) {
  AddFragFromFile(File{path});
}
void ShaderProgramBuilder::AddVertFromFile(File& file) {
  AddVert(file.ReadString());
}
void ShaderProgramBuilder::AddFragFromFile(File& file) {
  AddFrag(file.ReadString());
}

void ShaderProgramBuilder::AttachShaders(int32_t handle) {
  auto attach_func = [handle](int32_t shader_handle) {
    glAttachShader(handle, shader_handle);
  };

  std::for_each(vert_handles.begin(), vert_handles.end(), attach_func);
  std::for_each(frag_handles.begin(), frag_handles.end(), attach_func);
}