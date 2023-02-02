cmake_minimum_required(VERSION 3.22)
project(badchessengine)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)

add_compile_options(-v)

add_executable(badchessengine main.cpp chess.cpp chess.h arg.cpp arg.h util.cpp util.h sdl_ui.cpp sdl_ui.h shell.cpp shell.h platform.cpp platform.h)
target_link_libraries(badchessengine ${CMAKE_SOURCE_DIR}/lib/libSDL2.a)
