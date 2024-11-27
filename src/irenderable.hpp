//
// Created by maksym on 11/27/24.
//

#include "shader.hpp"

#ifndef CV_TRICKS_IRENDERABLE_HPP
#define CV_TRICKS_IRENDERABLE_HPP

class IRenderable {
 public:
  Shader& shader;

  explicit IRenderable(Shader& shaderInstance) : shader(shaderInstance) {}
  virtual ~IRenderable() = default;
  virtual void initialize() = 0;
  virtual void render() = 0;
};

#endif  // CV_TRICKS_IRENDERABLE_HPP
