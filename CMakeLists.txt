cmake_minimum_required(VERSION 3.8)

project(loop-in-thread)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Gui Widgets)

set(SRCS main.cpp MainWindow.cpp)
set(HDRS MainWindow.h)
set(UIS MainWindow.ui)
set(QRCS )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

source_group("Resources" FILES ${UIS} ${QRCS})

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} ${UIS} ${QRCS})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Gui)
