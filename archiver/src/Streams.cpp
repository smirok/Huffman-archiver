#include "Streams.h"
#include <climits>
#include <iostream>

uint8_t OBitStream::unpacked_bits = CHAR_BIT;
uint8_t OBitStream::buffer = 0;

int8_t IBitStream::unreaded_bits = 0;
uint8_t IBitStream::buffer = 0;

OBitStream::operator bool() const {
    return !file.fail();
}

OBitStream &OBitStream::operator<<(uint8_t num) {
    file.write(reinterpret_cast<const char *>(&num), sizeof(num));
    return *this;
}

OBitStream &OBitStream::operator<<(bool bit) {
    buffer |= (bit << (unpacked_bits - 1));
    --unpacked_bits;
    if (unpacked_bits == 0) {
        file.write(reinterpret_cast<const char *>(&buffer), sizeof(buffer));
        buffer = 0;
        unpacked_bits = CHAR_BIT;
    }
    return *this;
}

OBitStream::OBitStream(std::ostream &out) noexcept: file(out) {}

OBitStream &OBitStream::operator<<(const std::vector<uint8_t> &code) {
    for (const auto &bit : code) {
        *this << static_cast<bool>(bit);
    }
    return *this;
}

OBitStream::~OBitStream() noexcept {
    if (unpacked_bits != CHAR_BIT) {
        file.write(reinterpret_cast<const char *>(&buffer), sizeof(buffer));
        buffer = 0;
        unpacked_bits = CHAR_BIT;
    }
}

IBitStream::operator bool() const {
    return !file.fail();
}

IBitStream::IBitStream(std::istream &in) noexcept: file(in){
}

void IBitStream::setIterPos(std::streampos pos) noexcept {
    file.seekg(pos);
}

IBitStream &IBitStream::operator>>(std::string &code) {
    for (char &bit : code)
        *this >> reinterpret_cast<uint8_t &>(bit);
    return *this;
}

IBitStream &IBitStream::operator>>(uint8_t &byte) {
    if (unreaded_bits == 0) {
        file.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
        unreaded_bits = CHAR_BIT;
    }
    byte = buffer & (1 << (--unreaded_bits)) ? 1 : 0;
    return *this;
}

void IBitStream::clear() noexcept {
    unreaded_bits = 0;
    buffer = 0;
}