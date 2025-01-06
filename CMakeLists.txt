cmake_minimum_required(VERSION 3.10)

project(TypeTest)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(rawterm)

add_executable(type src/main.cpp)

target_link_libraries(type PUBLIC rawterm)

# Add the include directory for the rawterm library

# NOTE: "PROJECT" refers to the current project. More important when there are submodules
#       "CMAKE" refers to the overall CMAKE structure
#       best to use "PROJECT" variables since that will increase scalability
target_include_directories(type PUBLIC 
    "${PROJECT_SOURCE_DIR}/rawterm"
    "${PROJECT_BINARY_DIRECTORY}"
)





