cmake_minimum_required(VERSION 3.29)
project(math_inter_wrapper)


project(math_inter_wrapper LANGUAGES CXX)

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
        QuickControls2
        Widgets
        REQUIRED
)

qt6_add_resources(math_inter_wrapper "resources"
        FILES
        views/TerminalView.qml
        views/TerminalStyle.qml
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
        Qt6::Quick
        Qt6::Qml
        Qt6::QuickControls2
        Qt6::Widgets
)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

#include(${CMAKE_CURRENT_SOURCE_DIR}/src/views/)
#
#if (LINK_INSIGHT)
#    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
#endif ()

# Define source directories for convenience
target_include_directories(math_inter_wrapper PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/models
        ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodels
)
