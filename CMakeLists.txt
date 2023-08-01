cmake_minimum_required(VERSION 3.5)

project(radio_receiver LANGUAGES CXX)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -g -O0")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(radio_receiver main.cpp)

#install(TARGETS radio_receiver
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/cmake)
add_subdirectory(src)
target_link_libraries(radio_receiver receiver)

