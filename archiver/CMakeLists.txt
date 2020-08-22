cmake_minimum_required(VERSION 3.10)
project(hw_03)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(include)

add_executable(hw_03 src/main.cpp
        src/CLI.cpp include/CLI.h
        src/HuffmanArchiver.cpp include/HuffmanArchiver.h
        src/Huffman.cpp include/Huffman.h
        src/Streams.cpp include/Streams.h)

add_executable(test_03 test/TestMain.cpp test/doctest.h
                    test/TestCLI.cpp include/CLI.h src/CLI.cpp
                    test/TestStreams.cpp include/Streams.h src/Streams.cpp
                    test/TestHuffman.cpp include/Huffman.h src/Huffman.cpp
                    test/TestHuffmanArchiver.cpp include/HuffmanArchiver.h src/HuffmanArchiver.cpp)