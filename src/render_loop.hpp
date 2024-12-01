//
// Created by maksym on 11/26/24.
//
#include <spdlog/spdlog.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "irenderable.hpp"

#ifndef CV_TRICKS_RENDER_LOOP_HPP
#define CV_TRICKS_RENDER_LOOP_HPP

static void glfw_error_callback(int error, const char* description) {
  spdlog::error("GLFW Error {}: {}", error, description);
}

class RenderLoop {
 public:
  std::vector<std::shared_ptr<IRenderable>> renderables;

  RenderLoop() = default;

  bool is_running = false;
  std::shared_ptr<GLFWwindow> window{};

  int initialize() {
    spdlog::info("Start init");
    glfwSetErrorCallback(glfw_error_callback);

    if (glfwInit() != 1) {
      spdlog::error("Failed to initialize GLFW");
      return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = std::shared_ptr<GLFWwindow>(
        glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
                         glfwGetVideoMode(glfwGetPrimaryMonitor())->height,
                         "Render program",
                         glfwGetPrimaryMonitor(),
                         nullptr),
        [](GLFWwindow* w) { glfwDestroyWindow(w); });

    if (window == nullptr) {
      spdlog::error(
          "Failed to open GLFW window. "
          "If you have an Intel GPU, they are not 3.3 compatible.");
      glfwTerminate();
      return -1;
    }
    glfwMakeContextCurrent(window.get());
    glfwSetInputMode(window.get(), GLFW_STICKY_KEYS, GL_TRUE);

    if (glewInit() != GLEW_OK) {
      spdlog::error("Failed to initialize GLEW");
      return -1;
    }

    for (const auto& renderable : renderables) {
      renderable->initialize(window);
    }

    spdlog::info("Finish init");
    return 1;
  };

  void shutdown() {
    spdlog::info("Shutting down render loop...");
    // renderer.cleanup();
    spdlog::info("Application terminated cleanly.");
  };
  void update(float deltaTime){};

  void render() {
    for (const auto& renderable : renderables) {
      renderable->render();
    }
  };

  int run() {
    auto status = initialize();
    if (status == -1) {
      return -1;
    }

    spdlog::info("Enter render loop...");
    is_running = true;

    while (is_running) {
      static double last_time = glfwGetTime();
      double current_time = glfwGetTime();
      auto delta_time = static_cast<float>(current_time - last_time);
      last_time = current_time;

      glfwPollEvents();

      update(delta_time);

      render();

      glfwSwapBuffers(window.get());
      glfwPollEvents();

      if (glfwWindowShouldClose(window.get()) ||
          glfwGetKey(window.get(), GLFW_KEY_ESCAPE)) {
        is_running = false;
      }
    }
    shutdown();
  };

  void add_renderable(const std::shared_ptr<IRenderable>& renderable) {
    renderables.push_back(renderable);
  }
};

#endif  // CV_TRICKS_RENDER_LOOP_HPP