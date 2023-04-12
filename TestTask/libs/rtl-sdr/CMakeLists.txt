cmake_minimum_required(VERSION 3.5)

project(rtl-sdr LANGUAGES C)

file(GLOB_RECURSE  SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h )

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME}
    tuner_e4k
    tuner_fc0012
    tuner_fc0013
    tuner_fc2580
    tuner_r82xx
    )

