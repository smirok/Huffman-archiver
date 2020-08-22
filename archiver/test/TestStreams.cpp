#include <iostream>
#include "doctest.h"
#include "Streams.h"

/*TEST_CASE ("test_IOBitStream_bool_>><<") {
    {
        OBitStream bitout("out7.bin");
        bool bit = true;
        bitout << bit;
    }
    uint8_t readed_bit = 0;
    IBitStream bitin("out6.bin");
    bitin.setIterPos(std::ios::beg);
    bitin >> readed_bit;

    remove("out6.bin");
    CHECK_EQ((int)readed_bit, 1);
}*/

TEST_CASE ("test_IOBitStream_string/vector<uint8_t>_>><<") {
    std::vector<uint8_t> code = {1, 0, 0, 1, 1, 1, 1, 0, 1};
    {
        OBitStream bitout("out1.bin");
        bitout << code;
    }
    IBitStream bitin("out1.bin");
    std::string str_code;
    str_code.resize(code.size());
    bitin.clear();
    bitin >> str_code;

    std::string ans;
    for (auto &bit : code)
        ans += bit;

    remove("out1.bin");
    CHECK_EQ(str_code, ans);
}