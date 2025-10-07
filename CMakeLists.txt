# Adapted from https://cliutils.gitlab.io/modern-cmake/README.html

cmake_minimum_required(VERSION 3.15...3.31)

project(tests)

set(CMAKE_C_STANDARD 99)       
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(rawterm)
# add_library(RawTerm rawterm/rawterm.c)

add_executable(TestExe   src/rawterm_test.cpp)
add_executable(Game      src/main.cpp        )
# NOTE: "PROJECT" refers to the current project. More important when there are submodules
#       "CMAKE" refers to the overall CMAKE structure
#       best to use "PROJECT" variables since that will increase scalability
# NOTE: include PROJECT_BINARY_DIRECTORY because that is where library is stored


target_include_directories(TestExe PUBLIC 
    "${CMAKE_SOURCE_DIR}/rawterm"
)

target_link_libraries(TestExe PUBLIC rawterm)

target_include_directories(Game PUBLIC 
    "${CMAKE_SOURCE_DIR}/rawterm"
    "${CMAKE_SOURCE_DIR}/include"
)
target_link_libraries(Game PUBLIC rawterm)

# add_executable(Type src/main.cpp)

# target_include_directories(Type PUBLIC 
#     "${CMAKE_SOURCE_DIR}/rawterm"
#     "${CMAKE_SOURCE_DIR}/include"
# )

# target_link_libraries(Type PUBLIC rawterm)
