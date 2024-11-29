//
// Created by maksym on 11/27/24.
//
#include <GL/glew.h>

#include "irenderable.hpp"
#include "shader.hpp"

#ifndef CV_TRICKS_RENDERABLES_HPP
#define CV_TRICKS_RENDERABLES_HPP

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

class FullScreenQuad : public IRenderable {
 public:
  unsigned int vao{}, vbo{}, ebo{};

  explicit FullScreenQuad(Shader& shader) : IRenderable(shader) {}

  void initialize() override {
    shader.load_shader();

    float quad_vertices[] = {
        // Positions    // TexCoords
        -1.0f,
        1.0f,
        0.0f,
        1.0f,  // Top-left
        -1.0f,
        -1.0f,
        0.0f,
        0.0f,  // Bottom-left
        1.0f,
        -1.0f,
        1.0f,
        0.0f,  // Bottom-right
        1.0f,
        1.0f,
        1.0f,
        1.0f  // Top-right
    };
    unsigned int quad_indices[] = {
        0,
        1,
        2,  // First triangle
        0,
        2,
        3  // Second triangle
    };

    // Generate VAO and VBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    // Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
        GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);

    // Element Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(quad_indices),
                 quad_indices,
                 GL_STATIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          4 * sizeof(float),
                          (void*)nullptr);  // Position

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          4 * sizeof(float),
                          (void*)(2 * sizeof(float)));  // TexCoords
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);  // Unbind VAO
  }

  ~FullScreenQuad() override {
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

class LightSource : public IRenderable {
 public:
  unsigned int vao{}, vbo{}, ebo{};
  float center_x;
  float center_y;
  float radius;

  int ATTRIB_VERTEX = 0;  // Location for vertex position attribute
  int ATTRIB_VALUE =
      1;  // Location for other attribute (e.g., texture coordinates)

  explicit LightSource(Shader& shader,
                       float center_x = 0.0,
                       float center_y = 0.0,
                       float radius = 0.0)
      : IRenderable(shader),
        center_x(center_x),
        center_y(center_y),
        radius(radius) {}

  void initialize() override {
    shader.load_shader();

    auto left = center_x - radius;
    auto right = center_x + radius;
    auto bottom = center_y - radius;
    auto top = center_y + radius;
    float quad[20] = {
        right, bottom, 0, 1.0,  -1.0, right, top,    0, 1.0,  1.0,
        left,  top,    0, -1.0, 1.0,  left,  bottom, 0, -1.0, -1.0,
    };

    // Generate and Bind Buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    unsigned int glBuffer;
    glGenBuffers(1, &glBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, quad, GL_STATIC_DRAW);

    // Configure Vertex Attributes
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_VALUE);
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, 20, nullptr);
    glVertexAttribPointer(
        ATTRIB_VALUE, 2, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(12));

    // unbind resources for safety
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  }

  ~LightSource() override {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
  }

  void render() override {
    shader.use();
    glBindVertexArray(vao);
    //  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
  }
};

#endif  // CV_TRICKS_RENDERABLES_HPP
