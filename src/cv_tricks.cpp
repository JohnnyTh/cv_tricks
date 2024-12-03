#include <spdlog/spdlog.h>

#include <array>

#include "render_loop.hpp"
#include "renderables.hpp"

int main(int argc, char* argv[]) {
  auto shader = Shader("../src/shaders/light_source.vert",
                       "../src/shaders/light_source.frag");

  auto light_1 = std::make_shared<LightSource>(
      shader, std::array<float, 3>({0.15, 0.3, 1.0}), 0.0, 0.0, 0.15, 0.35, 3.0, 7.0, 0.6);

//  auto light_2 = std::make_shared<LightSource>(
//      shader, std::array<float, 3>({0.0, 0.0, 1.0}), 0.1, 0.1, 0.05, 0.35);

  auto loop = RenderLoop();

  loop.add_renderable(light_1);
  //loop.add_renderable(light_2);

  loop.initialize();

  loop.run();
}