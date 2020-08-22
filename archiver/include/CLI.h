#ifndef HW_03_CLI_H
#define HW_03_CLI_H

#include <iostream>
#include <fstream>

enum Mode {
    ARCH_MODE = 'c',
    UNARCH_MODE = 'u'
};

// =================EXCEPTION==================

class CLException : public std::runtime_error {
public:
    explicit CLException(const std::string &error_message) :
            std::runtime_error(error_message) {};

    const char *what() const noexcept {
        return this->error_message_.c_str();
    };
private:
    std::string error_message_;
};

// ===================CLI====================

class CLI {
public:
    CLI(int argc, char **argv);

    Mode getMode() const noexcept;

    std::string getInputFile() const noexcept;

    std::string getOutputFile() const noexcept;

private:
    Mode mode;
    std::string input_file, output_file;

    static constexpr uint8_t CORRECT_ARGC = 6;
};

#endif //HW_03_CLI_H
