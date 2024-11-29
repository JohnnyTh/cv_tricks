#include <spdlog/spdlog.h>

#include "render_loop.hpp"
#include "renderables.hpp"

int main(int argc, char* argv[]) {
  auto shader = Shader("../src/shaders/light_source.vert",
                       "../src/shaders/light_source.frag");

  auto quad = std::make_shared<LightSource>(shader, 0.0, 0.0, 0.1);

  auto loop = RenderLoop();
  loop.add_renderable(quad);
  loop.initialize();

  loop.run();
}