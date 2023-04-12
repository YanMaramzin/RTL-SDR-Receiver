cmake_minimum_required(VERSION 3.5)

project(ReceiverHWImpl LANGUAGES CXX C)

file(GLOB_RECURSE  SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h )

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} Ireceiver)
target_link_libraries(${PROJECT_NAME} convenience)
target_link_libraries(${PROJECT_NAME} rtl-sdr)
target_link_libraries(${PROJECT_NAME} Complex)
