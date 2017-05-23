cmake_minimum_required(VERSION 3.6)
project(Metro_helper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_PREFIX_PATH "/Applications/Qt/5.8/clang_64")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCE_FILES
        drawpad.cpp
        drawpad.h
        kernel.cpp
        kernel.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        rsc.qrc
        NetworkFlow.h NetworkFlow.cpp NetworkFlow.cpp NetworkFlow.h Point.cpp Point.h
        line.h line.cpp)

add_executable(Metro_helper ${SOURCE_FILES})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

target_link_libraries(Metro_helper Qt5::Widgets)
target_link_libraries(Metro_helper Qt5::Core)
target_link_libraries(Metro_helper Qt5::Gui)
