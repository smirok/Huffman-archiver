cmake_minimum_required(VERSION 3.5)

project(huffman-archiver LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(app/include archiver/include)

if(ANDROID)
  add_library(huffman-archiver SHARED
      app/src/main.cpp
      app/src/mainwindow.cpp
      app/include/mainwindow.h
      app/src/mainwindow.ui
      app/src/presswindow.cpp
      app/include/presswindow.h
      app/src/presswindow.ui
      archiver/include/CLI.h
      archiver/include/Huffman.h
      archiver/include/HuffmanArchiver.h
      archiver/include/Streams.h
      archiver/src/CLI.cpp
      archiver/src/Huffman.cpp
      archiver/src/HuffmanArchiver.cpp
      archiver/src/Streams.cpp
  )
else()
  add_executable(huffman-archiver
    app/src/main.cpp
    app/src/mainwindow.cpp
    app/include/mainwindow.h
    app/src/mainwindow.ui
    app/src/presswindow.cpp
    app/include/presswindow.h
    app/src/presswindow.ui
    archiver/include/CLI.h
    archiver/include/Huffman.h
    archiver/include/HuffmanArchiver.h
    archiver/include/Streams.h
    archiver/src/CLI.cpp
    archiver/src/Huffman.cpp
    archiver/src/HuffmanArchiver.cpp
    archiver/src/Streams.cpp
  )
endif()

target_link_libraries(huffman-archiver PRIVATE Qt5::Widgets)
