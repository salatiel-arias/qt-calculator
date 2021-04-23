cmake_minimum_required(VERSION 3.5)

project(calculatorProject LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Threads REQUIRED)


add_executable(calculatorProject
                main.cpp
                mainwindow.cpp
                mainwindow.h)

add_library(customButtonsLib STATIC keypadButton.cpp)
target_link_libraries(customButtonsLib PUBLIC Qt5::Widgets)

add_library(calcEngineLib STATIC calcEngine.cpp)
target_link_libraries(calcEngineLib PRIVATE ${CMAKE_THREAD_LIBS_INIT} Qt5::Core)

target_link_libraries(calculatorProject PRIVATE  customButtonsLib calcEngineLib Qt5::Widgets)

