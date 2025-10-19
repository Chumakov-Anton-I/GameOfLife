cmake_minimum_required(VERSION 3.10)

project(GameOfLife VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)

    qt_add_executable(game MANUAL_FINALIZATION
        src/main.cpp
        src/mainwindow.h src/mainwindow.cpp
        src/map.h src/map.cpp
        src/grid.h src/grid.cpp)
else()
    if(ANDROID)
        add_library(game SHARED main.cpp)
    else()
        add_executable(game main.cpp)
    endif()
endif()

target_link_libraries(game PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(game PRIVATE Qt6::Core Qt6::Widgets)
target_link_libraries(game PRIVATE Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set_target_properties(game PROPERTIES MACOSX_BUNDLE TRUE)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(game)
endif()
