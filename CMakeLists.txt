cmake_minimum_required(VERSION 3.5)

project(receiver LANGUAGES CXX C)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -g -O0")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE STREQUAL Release)
add_executable(radio_receiver main.cpp)
endif()

include(GenerateExportHeader)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if (CMAKE_BUILD_TYPE STREQUAL Release)
target_link_libraries(radio_receiver receiver)
endif()

find_package(PkgConfig REQUIRED)
find_package(LibUSB REQUIRED)
find_package(Threads)

if(NOT LIBUSB_FOUND)
    message(FATAL_ERROR "LibUSB 1.0 required to compile rtl-sdr")
endif()
if(NOT THREADS_FOUND)
    message(FATAL_ERROR "pthreads(-win32) required to compile rtl-sdr")
endif()

file(GLOB SRC include/${PROJECT_NAME}/*.h src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC})

#add_subdirectory(libs/librtlsdr)
#add_subdirectory(libs/share)

generate_export_header(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${LIBUSB_INCLUDE_DIR}
    ${THREADS_PTHREADS_INCLUDE_DIR}
)


target_link_libraries(${PROJECT_NAME} ${LIBUSB_LIBRARIES})
target_link_libraries(${PROJECT_NAME} fftw3)
target_link_libraries(${PROJECT_NAME} rtlsdr)
target_link_libraries(${PROJECT_NAME} DSP)
target_link_libraries(${PROJECT_NAME} Base)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/receiver)
