#pragma once

#include <memory>
#include <string>
#include <vector>

class ShaderProgram;
class File;

class ShaderProgramBuilder {
  std::vector<int32_t> vert_handles;
  std::vector<int32_t> frag_handles;

  void AttachShaders(int32_t handle);

  void AddShader(const std::string& src, int32_t shader_handle);

 public:
  void AddVert(const std::string& src);
  void AddFrag(const std::string& src);

  void AddVertFromFile(const std::string& path);
  void AddFragFromFile(const std::string& path);
  void AddVertFromFile(File& file);
  void AddFragFromFile(File& file);
  std::unique_ptr<ShaderProgram> Build();
};