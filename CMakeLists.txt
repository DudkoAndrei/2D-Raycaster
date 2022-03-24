cmake_minimum_required(VERSION 3.21)
project(2D-Raycaster)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Raycaster
        main.cpp
        src/Ray/ray.cpp)

target_link_libraries(Raycaster
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )