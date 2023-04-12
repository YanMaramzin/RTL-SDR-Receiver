cmake_minimum_required(VERSION 3.5)

project(tuner_fc2580 LANGUAGES C)

file(GLOB_RECURSE  SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h )

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(${PROJECT_NAME}
    ${LIBUSB_LIBRARIES}
)


