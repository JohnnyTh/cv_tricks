cmake_minimum_required(VERSION 3.15)
project(cv_tricks CXX)

find_package("spdlog" REQUIRED)

add_executable(${PROJECT_NAME} "src/cv_tricks.cpp")
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)