#include "doctest.h"
#include "HuffmanArchiver.h"
#include <random>
#include <iostream>
#include <thread>
#include <sstream>

TEST_CASE ("test_compress&decompess_small") {
    std::mt19937 randomer(5);
    unsigned char text[100];
    for (int i = 0; i < 100; ++i) {
        text[i] = (unsigned char) (randomer() % 25 + 97);
    }

    std::ofstream out("input3.txt");
    out.write(reinterpret_cast<char *>(&text), sizeof(text));
    out.close();

    HuffmanArchiver ha;
    std::stringstream kek;
    ha.compress(kek,"out3.edb");
    ha.decompress("out3.edb","input4.txt");

    std::ifstream input("input3.txt", std::ios::binary);
    std::ifstream input1("input4.txt", std::ios::binary);
    char letter, letter1;
    bool is_equal = true;
    while (input.get(reinterpret_cast<char &>(letter)) && input1.get(reinterpret_cast<char &>(letter1))) {
        if (letter != letter1){
            is_equal = false;
            break;
        }
    }
    input.close();
    input1.close();
    remove("out3.edb");
    remove("input3.txt");
    remove("input4.txt");
    CHECK_EQ(is_equal,true);
}