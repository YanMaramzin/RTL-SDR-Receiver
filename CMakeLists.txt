# Copyright 2012 OSMOCOM Project
#
# This file is part of rtl-sdr
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 3.5)
#set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project(receiver CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

if(NOT LIB_INSTALL_DIR)
   set(LIB_INSTALL_DIR lib)
endif()



########################################################################
# Compiler specific setup
########################################################################
#if(CMAKE_COMPILER_IS_GNUCC AND NOT WIN32)
#    ADD_DEFINITIONS(-Wall)
#    ADD_DEFINITIONS(-Wextra)
#    ADD_DEFINITIONS(-Wno-unused-parameter)
#    ADD_DEFINITIONS(-Wno-unused)
#    ADD_DEFINITIONS(-Wsign-compare)
#    ADD_DEFINITIONS(-Wdeclaration-after-statement)
#    #http://gcc.gnu.org/wiki/Visibility
##    ADD_DEFINITIONS(-fvisibility=hidden)
#endif()


########################################################################
# Find build dependencies
########################################################################
find_package(PkgConfig)
find_package(LibUSB)
set(THREADS_USE_PTHREADS_WIN32 true)
find_package(Threads)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Network PrintSupport)


if(NOT LIBUSB_FOUND)
    message(FATAL_ERROR "LibUSB 1.0 required to compile rtl-sdr")
endif()
if(NOT THREADS_FOUND)
    message(FATAL_ERROR "pthreads(-win32) required to compile rtl-sdr")
endif()
########################################################################
# Setup the include and linker paths
########################################################################
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${LIBUSB_INCLUDE_DIR}
    ${THREADS_PTHREADS_INCLUDE_DIR}
)

#link_directories(
#    ...
#)

# Set component parameters
#set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "" FORCE)

########################################################################
# Create uninstall target
########################################################################
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
@ONLY)

add_custom_target(uninstall
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)

########################################################################
# Install udev rules
########################################################################
option(INSTALL_UDEV_RULES "Install udev rules for RTL-SDR" OFF)
if (INSTALL_UDEV_RULES)
    install (
        FILES rtl-sdr.rules
        DESTINATION "/etc/udev/rules.d"
        COMPONENT "udev"
        )
else (INSTALL_UDEV_RULES)
    message (STATUS "Udev rules not being installed, install them with -DINSTALL_UDEV_RULES=ON")
endif (INSTALL_UDEV_RULES)

option(DETACH_KERNEL_DRIVER "Detach kernel driver if loaded" OFF)
if (DETACH_KERNEL_DRIVER)
    message (STATUS "Building with kernel driver detaching enabled")
    add_definitions(-DDETACH_KERNEL_DRIVER=1)
else (DETACH_KERNEL_DRIVER)
    message (STATUS "Building with kernel driver detaching disabled, use -DDETACH_KERNEL_DRIVER=ON to enable")
endif (DETACH_KERNEL_DRIVER)

########################################################################
# Add subdirectories
########################################################################
add_subdirectory(TestTask/libs/rtl-sdr)
add_subdirectory(TestTask/libs/convenience)
add_subdirectory(TestTask/libs/tuner_e4k)
add_subdirectory(TestTask/libs/tuner_fc0012)
add_subdirectory(TestTask/libs/tuner_fc0013)
add_subdirectory(TestTask/libs/tuner_fc2580)
add_subdirectory(TestTask/libs/tuner_r82xx)
add_subdirectory(TestTask/libs/Ireceiver)
add_subdirectory(TestTask/libs/ReceiverHWImpl)
add_subdirectory(TestTask/libs/ReceiverSoftImpl)
add_subdirectory(TestTask/libs/qcustomplot)
add_subdirectory(TestTask/libs/Complex)
add_subdirectory(TestTask/libs/Filter)
add_subdirectory(TestTask/libs/fft)
add_subdirectory(TestTask/libs/window)
add_subdirectory(TestTask/libs/WavReader)



########################################################################
# Create Pkg Config File
########################################################################
FOREACH(inc ${LIBUSB_INCLUDE_DIR})
    LIST(APPEND RTLSDR_PC_CFLAGS "-I${inc}")
ENDFOREACH(inc)

FOREACH(lib ${LIBUSB_LIBRARY_DIRS})
    LIST(APPEND RTLSDR_PC_LIBS "-L${lib}")
ENDFOREACH(lib)

# use space-separation format for the pc file
STRING(REPLACE ";" " " RTLSDR_PC_CFLAGS "${RTLSDR_PC_CFLAGS}")
STRING(REPLACE ";" " " RTLSDR_PC_LIBS "${RTLSDR_PC_LIBS}")

# unset these vars to avoid hard-coded paths to cross environment
IF(CMAKE_CROSSCOMPILING)
    UNSET(RTLSDR_PC_CFLAGS)
    UNSET(RTLSDR_PC_LIBS)
ENDIF(CMAKE_CROSSCOMPILING)

set(prefix ${CMAKE_INSTALL_PREFIX})
set(exec_prefix \${prefix})
set(libdir \${exec_prefix}/${LIB_INSTALL_DIR})
set(includedir \${prefix}/include)

CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/librtlsdr.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/librtlsdr.pc
@ONLY)

INSTALL(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/librtlsdr.pc
    DESTINATION ${LIB_INSTALL_DIR}/pkgconfig
)

########################################################################
# Print Summary
########################################################################
MESSAGE(STATUS "Building for version: ${VERSION} / ${LIBVER}")
MESSAGE(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")


add_executable(receiver main.cpp)

target_link_libraries(${PROJECT_NAME} convenience)
target_link_libraries(${PROJECT_NAME} Ireceiver)
target_link_libraries(${PROJECT_NAME} ReceiverHWImpl)
target_link_libraries(${PROJECT_NAME} ReceiverSoftImpl)
target_link_libraries(${PROJECT_NAME} Complex)
target_link_libraries(${PROJECT_NAME} Filter)
target_link_libraries(${PROJECT_NAME} fft)
target_link_libraries(${PROJECT_NAME} window)
target_link_libraries(${PROJECT_NAME} WavReader)

target_link_libraries(
    ${PROJECT_NAME}
    qcustomplot
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    Qt5::PrintSupport
    )
