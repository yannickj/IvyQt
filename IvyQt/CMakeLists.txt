cmake_minimum_required(VERSION 3.14)

project(IvyQt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)

add_library(IvyQt STATIC
  ivyqt.cpp
  ivyqt.h
  peer.cpp
  peer.h
)

target_link_libraries(IvyQt PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
)


target_compile_definitions(IvyQt PRIVATE IVYQT_LIBRARY)


install(TARGETS IvyQt DESTINATION lib)
install(FILES ivyqt.h peer.h DESTINATION include)
