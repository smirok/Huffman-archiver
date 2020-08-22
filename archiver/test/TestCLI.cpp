#include "doctest.h"
#include "CLI.h"

TEST_CASE ("test_getMode_arch") {
    const char *test_argv[6];
    test_argv[0] = "./hw_03";
    test_argv[1] = "-c";
    test_argv[2] = "-f";
    test_argv[3] = "input.txt";
    test_argv[4] = "-o";
    test_argv[5] = "output.txt";
    CLI cli(6, const_cast<char **>(test_argv));
    CHECK_EQ(cli.getMode(), Mode::ARCH_MODE);
}

TEST_CASE ("test_getMode_unarch") {
    const char *test_argv[6];
    test_argv[0] = "./hw_03";
    test_argv[1] = "-u";
    test_argv[2] = "-f";
    test_argv[3] = "input.txt";
    test_argv[4] = "-o";
    test_argv[5] = "output.txt";
    CLI cli(6, const_cast<char **>(test_argv));
    CHECK_EQ(cli.getMode(), Mode::UNARCH_MODE);
}

TEST_CASE ("test_getInputFile_short") {
    const char *test_argv[6];
    test_argv[0] = "./hw_03";
    test_argv[1] = "-c";
    test_argv[2] = "-f";
    test_argv[3] = "input.txt";
    test_argv[4] = "-o";
    test_argv[5] = "output.txt";
    CLI cli(6, const_cast<char **>(test_argv));
    CHECK_EQ(cli.getInputFile(), test_argv[3]);
}

TEST_CASE ("test_getInputFile_long") {
    const char *test_argv[6];
    test_argv[0] = "./hw_03";
    test_argv[1] = "-u";
    test_argv[2] = "--file";
    test_argv[3] = "input.txt";
    test_argv[4] = "-o";
    test_argv[5] = "output.txt";
    CLI cli(6, const_cast<char **>(test_argv));
    CHECK_EQ(cli.getInputFile(), test_argv[3]);
}

TEST_CASE ("test_getOutputFile_short") {
    const char *test_argv[6];
    test_argv[0] = "./hw_03";
    test_argv[1] = "-u";
    test_argv[2] = "-f";
    test_argv[3] = "input.txt";
    test_argv[4] = "-o";
    test_argv[5] = "output.txt";
    CLI cli(6, const_cast<char **>(test_argv));
    CHECK_EQ(cli.getOutputFile(), test_argv[5]);
}

TEST_CASE ("test_getOutputFile_long") {
    const char *test_argv[6];
    test_argv[0] = "./hw_03";
    test_argv[1] = "-u";
    test_argv[2] = "-f";
    test_argv[3] = "input.txt";
    test_argv[4] = "--output";
    test_argv[5] = "output.txt";
    CLI cli(6, const_cast<char **>(test_argv));
    CHECK_EQ(cli.getOutputFile(), test_argv[5]);
}

TEST_CASE ("test_parseInput_right_order") {
    const char *test_argv[6];
    test_argv[0] = "./hw_03";
    test_argv[1] = "-c";
    test_argv[2] = "-f";
    test_argv[3] = "input.txt";
    test_argv[4] = "-o";
    test_argv[5] = "output.txt";
    CLI cli(6, const_cast<char **>(test_argv));
    CHECK_EQ(cli.getMode(), Mode::ARCH_MODE);
    CHECK_EQ(cli.getInputFile(), test_argv[3]);
    CHECK_EQ(cli.getOutputFile(), test_argv[5]);
}

TEST_CASE ("test_parseInput_reverse_order") {
    const char *test_argv[6];
    test_argv[0] = "./hw_03";
    test_argv[1] = "-o";
    test_argv[2] = "output.txt";
    test_argv[3] = "-f";
    test_argv[4] = "input.txt";
    test_argv[5] = "-c";
    CLI cli(6, const_cast<char **>(test_argv));
    CHECK_EQ(cli.getMode(), Mode::ARCH_MODE);
    CHECK_EQ(cli.getInputFile(), test_argv[4]);
    CHECK_EQ(cli.getOutputFile(), test_argv[2]);
}

TEST_CASE ("test_parseInput_shuffle_order") {
    const char *test_argv[6];
    test_argv[0] = "./hw_03";
    test_argv[1] = "--output";
    test_argv[2] = "output.txt";
    test_argv[3] = "-u";
    test_argv[4] = "-f";
    test_argv[5] = "input.txt";
    CLI cli(6, const_cast<char **>(test_argv));
    CHECK_EQ(cli.getMode(), Mode::UNARCH_MODE);
    CHECK_EQ(cli.getInputFile(), test_argv[5]);
    CHECK_EQ(cli.getOutputFile(), test_argv[2]);
}

TEST_CASE ("test_parseInput_wrong_argc") {
    const char *test_argv[5];
    test_argv[0] = "./hw_03";
    test_argv[1] = "-u";
    test_argv[2] = "-f";
    test_argv[3] = "input.txt";
    test_argv[4] = "-o";
    CHECK_THROWS(CLI(5, const_cast<char **>(test_argv)));
}

TEST_CASE ("test_parseInput_wrong_argv") {
    const char *test_argv[6];
    test_argv[0] = "q";
    test_argv[1] = "w";
    test_argv[2] = "s";
    test_argv[3] = "a";
    test_argv[4] = "f";
    test_argv[5] = "d";
    CHECK_THROWS(CLI(6, const_cast<char **>(test_argv)));
}

TEST_CASE ("test_parseInput_wrong_sequence") {
    const char *test_argv[6];
    test_argv[0] = "./hw_03";
    test_argv[1] = "-u";
    test_argv[2] = "-f";
    test_argv[3] = "input.txt";
    test_argv[4] = "output.txt";
    test_argv[5] = "-o";
    CHECK_THROWS(CLI(6, const_cast<char **>(test_argv)));
}