cmake_minimum_required(VERSION 3.21)
project(2D-Raycaster)

set(CMAKE_CXX_STANDARD 20)
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
        src/AreaSettingsDialog/area_settings_dialog.cpp
        src/Controller/controller.cpp
        src/MainWindow/main_window.cpp
        src/PaintWidget/paint_widget.cpp
        src/Polygon/polygon.cpp
        src/Ray/ray.cpp)

target_link_libraries(Raycaster
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
