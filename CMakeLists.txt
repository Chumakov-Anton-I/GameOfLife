cmake_minimum_required(VERSION 3.10)

project(GameOfLife VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SRC_FILES
    src/main.cpp
    src/mainwindow.h src/mainwindow.cpp
    src/map.h src/map.cpp
    src/grid.h src/grid.cpp
)

if(WIN32)
    list(APPEND SRC_FILES src/win32/game.rc)
    file(WRITE
        ${CMAKE_CURRENT_BINARY_DIR}/rcVersion.h
        "#define GAME_MAJOR_VERSION ${PROJECT_VERSION_MAJOR}\n"
        "#define GAME_MINOR_VERSION ${PROJECT_VERSION_MINOR}\n"
        "#define GAME_PATCH_VERSION ${PROJECT_VERSION_PATCH}\n"
        "#define GAME_DOTTED_VERSION \"${PROJECT_VERSION}\"\n"
    )
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
    qt_add_executable(game MANUAL_FINALIZATION ${SRC_FILES})
#else() # TODO
endif()

target_include_directories(game PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(game PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(game PRIVATE Qt6::Core Qt6::Widgets)
target_link_libraries(game PRIVATE Qt6::Widgets)

########## INSTALLATION ##########
include(GNUInstallDirs)
install(TARGETS game
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET game
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

set_target_properties(game PROPERTIES MACOSX_BUNDLE TRUE)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(game)
endif()
