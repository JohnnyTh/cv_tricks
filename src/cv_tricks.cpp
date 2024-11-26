#include <spdlog/spdlog.h>

#include <string>
#include <vector>

#include "render_loop.hpp"

void cv_tricks_print_vector(const std::vector<std::string>& strings) {
  for (const auto& string : strings) {
    spdlog::info("cv_tricks/0.1 {}", string);
  }
}

int main(int argc, char* argv[]) {
  auto loop = RenderLoop();
  loop.run();
}