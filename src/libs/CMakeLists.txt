cmake_minimum_required(VERSION 3.7)

project(receiver LANGUAGES CXX C)

include(GenerateExportHeader)
#list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if(NOT ${LIB_INSTALL_DIR})
   set(${LIB_INSTALL_DIR} lib)
endif()

find_package(PkgConfig REQUIRED)
find_package(LibUSB REQUIRED)
find_package(Threads)
find_package(fftw3)

if(NOT LIBUSB_FOUND)
    message(FATAL_ERROR "LibUSB 1.0 required to compile rtl-sdr")
endif()
if(NOT THREADS_FOUND)
    message(FATAL_ERROR "pthreads(-win32) required to compile rtl-sdr")
endif()


add_library(${PROJECT_NAME} SHARED
    include/ireceiver.h
    include/receiverwrapper.h
    include/complex.h

    src/fft.h
    src/fft.cpp
    src/receiverhwimpl.h
    src/receiverhwimpl.cpp
    src/receiversoftimpl.h
    src/receiversoftimpl.cpp
    src/receiverwrapper.cpp
#    share/rtl-sdr.h
#    share/librtlsdr.c
#    share/reg_field.h
#    share/rtl-sdr_export.h
#    share/rtlsdr_i2c.h
#    share/tuner_e4k.h
#    share/tuner_e4k.c
#    share/tuner_fc0012.h
#    share/tuner_fc0012.c
#    share/tuner_fc0013.h
#    share/tuner_fc0013.c
#    share/tuner_fc2580.h
#    share/tuner_fc2580.c
#    share/tuner_r82xx.h
#    share/tuner_r82xx.c

)

add_subdirectory(librtlsdr)

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