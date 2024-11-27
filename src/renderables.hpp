//
// Created by maksym on 11/27/24.
//
#include <GL/glew.h>

#include "irenderable.hpp"
#include "shader.hpp"

#ifndef CV_TRICKS_RENDERABLES_HPP
#define CV_TRICKS_RENDERABLES_HPP

class FullScreenQuad : public IRenderable {
 public:

  unsigned int vao{}, vbo{}, ebo{};

  explicit FullScreenQuad(Shader& shader) : IRenderable(shader) {}

  void initialize() override {
    shader.load_shader();

    float quad_vertices[] = {
        // Positions    // TexCoords
        -1.0f, 1.0f,  0.0f, 1.0f,  // Top-left
        -1.0f, -1.0f, 0.0f, 0.0f,  // Bottom-left
        1.0f,  -1.0f, 1.0f, 0.0f,  // Bottom-right
        1.0f,  1.0f,  1.0f, 1.0f   // Top-right
    };
    unsigned int quad_indices[] = {
        0, 1, 2,  // First triangle
        0, 2, 3   // Second triangle
    };

    // Generate VAO and VBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    // Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices,
                 GL_STATIC_DRAW);

    // Element Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_indices), quad_indices,
                 GL_STATIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void*)nullptr);  // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void*)(2 * sizeof(float)));  // TexCoords
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);  // Unbind VAO
  }

  ~FullScreenQuad() override  {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
  }

  void render() override {
    shader.use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
  }
};

#endif  // CV_TRICKS_RENDERABLES_HPP
