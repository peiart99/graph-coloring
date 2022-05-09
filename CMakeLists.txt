cmake_minimum_required(VERSION 3.20)
project(graph_coloring)

set(CMAKE_CXX_STANDARD 17)
add_executable(graph_coloring main.cpp Graph.cpp Graph.h GraphLoader.cpp GraphLoader.h GraphColoring.cpp GraphColoring.h UserInterface.cpp UserInterface.h Vertex.cpp Vertex.h)
target_link_options(graph_coloring PRIVATE -static-libgcc -static-libstdc++)
