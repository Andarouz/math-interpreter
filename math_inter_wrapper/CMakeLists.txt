cmake_minimum_required(VERSION 3.29)
project(math_inter_wrapper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find necessary Qt components
find_package(Qt6 COMPONENTS
        Core
        Gui
        Qml
        Quick
        Widgets
        REQUIRED
)

qt6_add_resources(math_inter_wrapper "resources"
        FILES
        src/views/TerminalView.qml
        src/views/TerminalStyle.qml
)

# Specify the executable and its sources
add_executable(math_inter_wrapper
        src/main.cpp
        src/models/TerminalModel.cpp
        src/models/TerminalModel.h
        src/viewmodels/TerminalViewModel.cpp
        src/viewmodels/TerminalViewModel.h
)

# Link with necessary Qt libraries
target_link_libraries(math_inter_wrapper
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::Widgets
)

# Define source directories for convenience
target_include_directories(math_inter_wrapper PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/models
        ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodels
)