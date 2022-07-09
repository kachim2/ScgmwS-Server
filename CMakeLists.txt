cmake_minimum_required(VERSION 3.14)
project(Cpp_GameServer VERSION 0.1)


add_subdirectory(sfml EXCLUDE_FROM_ALL)



add_executable(Cpp_GameServer main.cpp)
target_link_libraries(Cpp_GameServer PUBLIC sfml-system sfml-network)


target_include_directories(Cpp_GameServer PUBLIC
                          "${PROJECT_BINARY_DIR}/sfml/lib"
                          "${PROJECT_SOURCE_DIR}/sfml/include"
                          )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
