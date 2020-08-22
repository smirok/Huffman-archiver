#include <iostream>
#include "HuffmanArchiver.h"
#include "CLI.h"
#include <cstdlib>
#include <fstream>

int main(int argc, char *argv[]) {
    static_assert(CHAR_BIT == 8, "Sorry :( Bit compressing won't be work");

    try {
        CLI cli(argc, argv);
        HuffmanArchiver ha;
        std::ifstream ifs(cli.getInputFile(), std::ifstream::binary);
        std::ofstream ofs(cli.getOutputFile(), std::ofstream::binary);

        if (cli.getMode() == Mode::ARCH_MODE)
            ha.compress(ifs,ofs);
        else
            ha.decompress(ifs,ofs);
    } catch (std::exception &exc) {
        std::cout << exc.what();
        return EXIT_FAILURE;
    }
    return 0;
}