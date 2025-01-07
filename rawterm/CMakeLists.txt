
project(rawterm)

add_library(rawterm STATIC src/rawterm.c)     

target_include_directories(rawterm PUBLIC "${PROJECT_SOURCE_DIR}/include")