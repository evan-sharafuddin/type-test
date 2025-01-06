project(RawTerm)

add_library(rawterm STATIC src/rawterm.c)

message( "{$PPROJECT_SOURCE_DIRECTORY}")
target_include_directories(rawterm PRIVATE 
                           "${PROJECT_SOURCE_DIRECTORY}/incude"
)                                