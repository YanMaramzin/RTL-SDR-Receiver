cmake_minimum_required(VERSION 3.0)
project(window)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets PrintSupport Sql Test Xml Network Concurrent)

file(GLOB_RECURSE  SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h )

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)

target_link_libraries(${PROJECT_NAME} ReceiverHWImpl)
target_link_libraries(${PROJECT_NAME} Complex)

target_link_libraries(
    ${PROJECT_NAME}
    qcustomplot
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    Qt5::PrintSupport
    )
