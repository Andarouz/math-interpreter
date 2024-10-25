cmake_minimum_required(VERSION 3.29)
project(math_inter_wrapper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(math_inter_wrapper main.cpp
        mainwindow.h
        mainwindow.cpp)
target_link_libraries(math_inter_wrapper
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)