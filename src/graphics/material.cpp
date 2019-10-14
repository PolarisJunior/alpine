#include "graphics/material.h"
#include "graphics/shader_program.h"
#include "graphics/shader_program_builder.h"

Material::Material(std::unique_ptr<ShaderProgram> program)
    : shader(std::move(program)) {}

Material::Material(const std::string& vert_file, const std::string& frag_file) {
  ShaderProgramBuilder program_builder{};
  program_builder.AddVertFromFile("resources/shaders/simple.vert");
  program_builder.AddFragFromFile("resources/shaders/simple.frag");
  shader = program_builder.Build();
}

Material::Material(const Material& mat) : shader(mat.shader) {}