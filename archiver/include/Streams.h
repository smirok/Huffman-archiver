#ifndef HW_03_BITSTREAM_H
#define HW_03_BITSTREAM_H

#include <fstream>
#include <vector>

class IBitStream {
public:
    IBitStream(std::istream& in) noexcept;

    IBitStream &operator>>(std::string &code);
    IBitStream &operator>>(uint8_t &byte);

    void setIterPos(std::streampos pos) noexcept;
    void clear() noexcept;
    operator bool() const;
private:
    static int8_t unreaded_bits;
    static uint8_t buffer;
    std::istream& file;
};

class OBitStream {
public:
    OBitStream(std::ostream& out) noexcept;
    ~OBitStream() noexcept;

    OBitStream &operator<<(const std::vector<uint8_t> &);
    OBitStream &operator<<(uint8_t num);
    OBitStream &operator<<(bool bit);
    operator bool() const;
private:
    static uint8_t unpacked_bits;
    static uint8_t buffer;
    std::ostream& file;
};

#endif //HW_03_BITSTREAM_H