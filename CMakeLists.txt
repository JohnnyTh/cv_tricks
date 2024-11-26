cmake_minimum_required(VERSION 3.15)
project(cv_tricks CXX)

find_package("spdlog" REQUIRED)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(
        ${PROJECT_NAME}
        "src/cv_tricks.cpp"
        "src/render_loop.hpp"
)
target_link_libraries(
        ${PROJECT_NAME}
        spdlog::spdlog
        glfw
        OpenGL::GL
        GLEW::GLEW
)