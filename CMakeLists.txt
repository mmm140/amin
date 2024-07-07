cmake_minimum_required(VERSION 3.28)
project(amin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(amin main.cpp
        src/Game.cpp
        src/Game.h
        src/Platform.cpp
        src/Platform.h
        src/Decorator.cpp
        src/Decorator.h
        src/Player.cpp
        src/Player.h
        src/Bodyobject.cpp
        src/Bodyobject.h
        src/Position.cpp
        src/Position.h
        sources/resources.qrc)
target_link_libraries(amin
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

