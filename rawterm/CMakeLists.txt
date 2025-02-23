cmake_minimum_required(VERSION 3.28)


project(rawterm)

add_library(rawterm STATIC src/rawterm.c)     

target_include_directories(rawterm PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(Button test/button_test.c)

target_include_directories(Button PUBLIC "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/src")