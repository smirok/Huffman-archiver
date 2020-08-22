#ifndef HW_03_HUFFMANARCHIVER_H
#define HW_03_HUFFMANARCHIVER_H

#include "Huffman.h"
#include "CLI.h"
#include "Streams.h"
#include <fstream>

#include <vector>

struct SizesHolder{
    uint32_t input_size = 0;
    uint32_t output_size = 0;
    uint32_t add_size = 0;
    uint32_t decoded_text_size = 0;
};

class HuffmanArchiver {
public:
    void compress(std::istream& in, std::ostream& out);
    void decompress(std::istream& in, std::ostream& out);

private:
    HuffmanTree tree;
    SizesHolder sh;

private:

    void loadFile(std::istream &in);

    void calcAddSize(const std::vector<uint8_t> &symbols);
    std::pair<std::vector<uint32_t>, std::vector<uint8_t>> getFreqsAndSymbols(std::istream &in) const;

    void outputAddInfo(std::ostream &out, std::vector<uint8_t> &symbols);
    void outputText(std::istream &in, std::ostream &out);

    void printStatistics();

    void readAddInfo(std::istream& in, IBitStream& bitin);
    void outputDecodedText(IBitStream& bitin, std::ostream& out);
};

#endif //HW_03_HUFFMANARCHIVER_H
