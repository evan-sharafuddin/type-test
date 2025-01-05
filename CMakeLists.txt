cmake_minimum_required(VERSION 3.10)

project(TypeTest)

set(CMAKE_CXX_STANDARD 20)

# Define the static library target from rawterm.c
add_library(rawterm STATIC src/rawterm.c)

add_executable(type ${CMAKE_SOURCE_DIR}/src/main.cpp)

target_link_libraries(type rawterm)

# Add the include directory for the rawterm library
target_include_directories(rawterm 
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)
target_include_directories(type 
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)




