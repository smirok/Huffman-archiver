#include "CLI.h"
#include <vector>

CLI::CLI(int argc, char **argv) noexcept(false) {
    if (argc != CORRECT_ARGC) {
        throw CLException("Incorrect number of parameters");
    }

    std::vector<std::string> arguments;
    arguments.assign(argv + 1, argv + CORRECT_ARGC);

    for (auto arg = arguments.begin(); arg != arguments.end(); ++arg) {
        if (*arg == "-c") {
            mode = Mode::ARCH_MODE;
        } else if (*arg == "-u") {
            mode = Mode::UNARCH_MODE;
        } else if (*arg == "-f" || *arg == "--file") {
            if (arg != --arguments.end())
                input_file = *(++arg);
        } else if (*arg == "-o" || *arg == "--output") {
            if (arg != --arguments.end())
                output_file = *(++arg);
        } else {
            throw CLException("Some parameters are incorrect");
        }
    }
}

Mode CLI::getMode() const noexcept {
    return mode;
}

std::string CLI::getInputFile() const noexcept {
    return input_file;
}

std::string CLI::getOutputFile() const noexcept {
    return output_file;
}