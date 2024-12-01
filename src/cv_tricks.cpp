#include <spdlog/spdlog.h>

#include <array>

#include "render_loop.hpp"
#include "renderables.hpp"

int main(int argc, char* argv[]) {
  auto shader = Shader("../src/shaders/light_source.vert",
                       "../src/shaders/light_source.frag");

  auto quad = std::make_shared<LightSource>(
      shader, std::array<float, 3>({1.0, 1.0, 0.0}), 0.0, 0.0, 0.4, 0.5);

  auto loop = RenderLoop();
  loop.add_renderable(quad);
  loop.initialize();

  loop.run();
}