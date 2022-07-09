cmake_minimum_required(VERSION 3.14)
project(Cpp_Game VERSION 0.1)


add_subdirectory(sfml EXCLUDE_FROM_ALL)



add_executable(Cpp_Game main.cpp SHA256.cpp)
target_link_libraries(Cpp_GameServer PUBLIC sfml-system sfml-network)


target_include_directories(Cpp_Game PUBLIC
                          "${PROJECT_BINARY_DIR}/sfml/lib"
                          "${PROJECT_SOURCE_DIR}/sfml/include"
                          )

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY maps DESTINATION ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
