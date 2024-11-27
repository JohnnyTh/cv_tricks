#include <spdlog/spdlog.h>

#include "render_loop.hpp"
#include "renderables.hpp"

int main(int argc, char* argv[]) {
  auto shader = Shader("../src/shaders/fullscreen_quad.vert",
                       "../src/shaders/fullscreen_quad.frag");

  auto quad = std::make_shared<FullScreenQuad>(shader);

  auto loop = RenderLoop();
  loop.add_renderable(quad);
  loop.initialize();

  loop.run();
}