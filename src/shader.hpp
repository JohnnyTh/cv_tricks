//
// Created by maksym on 11/27/24.
//
#include <GL/glew.h>

#include <stdexcept>
#include <string>
#include <utility>

#include "utilities/utils_shaders.hpp"

#ifndef CV_TRICKS_SHADER_HPP
#define CV_TRICKS_SHADER_HPP

class Shader {
 public:
  GLuint program_id = 0;
  std::string vertex_path;
  std::string fragment_path;

  Shader(std::string vertex_path_in, std::string fragment_path_in)
      : vertex_path(std::move(vertex_path_in)),
        fragment_path(std::move(fragment_path_in)) {}

  void load_shader() {
    // should be called within RenderLoop only after the proper OpenGL
    // context is created (e.g. GLFWwindow* window is created)
    program_id = utils_shaders::load_shaders(vertex_path, fragment_path);
    check_program_loaded();
  }

  void check_program_loaded() const {
    if (program_id == 0) {
      auto msg = ("Error loading shader " + vertex_path + ", " + fragment_path);
      spdlog::error(msg);
      throw std::runtime_error(msg);
    }
  }

  void use() const {
    check_program_loaded();
    glUseProgram(program_id);
  }
};

#endif  // CV_TRICKS_SHADER_HPP
