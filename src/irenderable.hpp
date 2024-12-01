//
// Created by maksym on 11/27/24.
//

#include "shader.hpp"

#ifndef CV_TRICKS_IRENDERABLE_HPP
#define CV_TRICKS_IRENDERABLE_HPP

class IRenderable {
 public:
  Shader& shader;
  std::shared_ptr<GLFWwindow> window = nullptr;

  explicit IRenderable(Shader& shaderInstance) : shader(shaderInstance) {}
  virtual ~IRenderable() = default;
  virtual void initialize(std::shared_ptr<GLFWwindow> new_window) = 0;
  virtual void render() = 0;

  [[nodiscard]] float get_aspect_ratio() const {
    int width, height;
    glfwGetFramebufferSize(window.get(), &width, &height);
    auto aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    return aspect_ratio;
  }

  void set_shader_aspect_ratio() const {
    int aspect_ratio_loc =
        glGetUniformLocation(shader.program_id, "aspectRatio");

    if (aspect_ratio_loc != -1) {
      glUniform1f(aspect_ratio_loc, get_aspect_ratio());
    }
  }
};

#endif  // CV_TRICKS_IRENDERABLE_HPP
