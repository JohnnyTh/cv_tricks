//
// Created by maksym on 11/27/24.
//
#include <GL/glew.h>

#include <array>

#include "irenderable.hpp"
#include "shader.hpp"

#ifndef CV_TRICKS_RENDERABLES_HPP
#define CV_TRICKS_RENDERABLES_HPP

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

class FullScreenQuad : public IRenderable {
 public:
  unsigned int vao{}, vbo{}, ebo{};

  explicit FullScreenQuad(Shader& shader) : IRenderable(shader) {}

  void initialize(std::shared_ptr<GLFWwindow> new_window) override {
    window = new_window;
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

  float outer_radius_initial;
  float inner_radius_initial;

  float outer_radius;
  float inner_radius;

  float oscillate_amplitude;
  float oscillate_frequency;

  std::array<float, 3> color_rgb;

  explicit LightSource(Shader& shader,
                       std::array<float, 3> color_rgb,
                       float center_x = 0.0,
                       float center_y = 0.0,
                       float inner_radius_initial = 0.0,
                       float outer_radius_initial = 0.0,
                       float oscillate_amplitude = 0.0,
                       float oscillate_frequency = 0.0)
      : IRenderable(shader),
        center_x(center_x),
        center_y(center_y),
        inner_radius_initial(inner_radius_initial),
        outer_radius_initial(outer_radius_initial),
        color_rgb(color_rgb),
        oscillate_amplitude(oscillate_amplitude),
        oscillate_frequency(oscillate_frequency) {
    outer_radius = outer_radius_initial;
    inner_radius = inner_radius_initial;
  }

  void initialize(std::shared_ptr<GLFWwindow> new_window) override {
    shader.load_shader();
    window = new_window;

    float vertices[] = {-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f};

    // Generate and Bind Buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  ~LightSource() override {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
  }

  void update(float delta_time, float time_passed_in_loop) override {
    float radians =
        2 * static_cast<float>(M_PI) * oscillate_frequency * time_passed_in_loop;

    inner_radius = oscillate_amplitude * sinf(radians) + inner_radius_initial;
    outer_radius = oscillate_amplitude * sinf(radians) + outer_radius_initial;
  }

  void render() override {
    shader.use();

    set_shader_aspect_ratio();

    auto center_loc = glGetUniformLocation(shader.program_id, "center");
    auto outer_radius_loc =
        glGetUniformLocation(shader.program_id, "outerRadius");
    auto inner_radius_loc =
        glGetUniformLocation(shader.program_id, "innerRadius");
    auto color_loc = glGetUniformLocation(shader.program_id, "color");

    // Update the uniform variables
    glUniform2f(center_loc, center_x, center_y);  // Center of the ring
    glUniform1f(outer_radius_loc, outer_radius);  // Outer radius
    glUniform1f(inner_radius_loc, inner_radius);  // Inner radius
    glUniform3fv(color_loc, 1, color_rgb.data());

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
  }
};

#endif  // CV_TRICKS_RENDERABLES_HPP
