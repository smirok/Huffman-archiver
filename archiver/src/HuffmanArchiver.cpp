#include "HuffmanArchiver.h"
#include <algorithm>
#include <climits>

constexpr uint32_t BUFFER_SIZE = CHAR_BIT << CHAR_BIT << CHAR_BIT;

void HuffmanArchiver::compress(std::istream &in, std::ostream &out) {
    loadFile(in);

    auto[freqs, symbols] = getFreqsAndSymbols(in); // vectors of freqs and symbols

    tree.Build(freqs);
    calcAddSize(symbols);

    outputAddInfo(out, symbols);
    outputText(in, out);

    printStatistics();
}

void HuffmanArchiver::loadFile(std::istream &in) {
    if (!in) {
        throw std::exception();
    }

    in.seekg(0, std::ios::end);
    sh.input_size = in.tellg();
    in.seekg(0, std::ios::beg);
}

std::pair<std::vector<uint32_t>, std::vector<uint8_t>> HuffmanArchiver::getFreqsAndSymbols(std::istream &in) const {
    std::vector<uint32_t> freqs(BYTE_ALPHABET_SIZE);
    std::vector<uint8_t> symbols;

    uint8_t buffer[BUFFER_SIZE];
    uint32_t cur_size = 0;

    while (cur_size < sh.input_size) {
        uint32_t size = BUFFER_SIZE < (sh.input_size - cur_size) ? BUFFER_SIZE : (sh.input_size - cur_size);
        in.read(reinterpret_cast<char *>(&buffer), size);
        cur_size += size;

        for (uint32_t i = 0; i < size; ++i) {
            if (!freqs[buffer[i]])
                symbols.push_back(buffer[i]);
            ++freqs[buffer[i]];
        }
    }
    return {freqs, symbols};
}

void HuffmanArchiver::calcAddSize(const std::vector<uint8_t> &symbols) {
    for (auto &symbol : symbols) {
        sh.add_size += tree[symbol].size();
    }

    sh.add_size = (sh.add_size % CHAR_BIT == 0) ? (sh.add_size / CHAR_BIT) : (sh.add_size / CHAR_BIT) + 1;

    sh.add_size = sh.add_size + (sizeof(uint16_t) * symbols.size()) +
                  sizeof(sh.input_size) + sizeof(sh.add_size) + sizeof(uint16_t);
}

void HuffmanArchiver::outputAddInfo(std::ostream &out, std::vector<uint8_t> &symbols) {
    if (!out)
        throw std::exception();

    out.write(reinterpret_cast<const char *>(&sh.add_size), sizeof(sh.add_size));
    out.write(reinterpret_cast<const char *>(&sh.input_size), sizeof(sh.input_size));

    uint16_t symbols_count = symbols.size();
    out.write(reinterpret_cast<const char *>(&symbols_count), sizeof(symbols_count));

    for (const auto &symbol : symbols) {
        out.write(reinterpret_cast<const char *>(&symbol), sizeof(symbol));
        uint8_t code_length = tree[symbol].size();
        out.write(reinterpret_cast<const char *>(&code_length), sizeof(code_length));
    }
    //out.close();

    OBitStream bitout(out);
    if (!bitout)
        throw std::exception();

    for (const auto &symbol : symbols) {
        bitout << tree[symbol];
    }
}

void HuffmanArchiver::outputText(std::istream &in, std::ostream &out) {
    OBitStream bitout(out);
    in.seekg(0, std::ios::beg);

    if (!in || !bitout)
        throw std::exception();

    uint8_t symbol;
    for (uint32_t i = 0; i < sh.input_size; ++i) {
        in.read(reinterpret_cast<char *>(&symbol), sizeof(symbol));
        sh.output_size += tree[symbol].size();
        bitout << tree[symbol];
    }

    sh.output_size = (sh.output_size % CHAR_BIT == 0) ? (sh.output_size / CHAR_BIT) : (sh.output_size / CHAR_BIT) + 1;
}

void HuffmanArchiver::printStatistics() {
    std::cout << sh.input_size << "\n" << sh.output_size << "\n" << sh.add_size << "\n";
}

void HuffmanArchiver::decompress(std::istream &in, std::ostream &out) {
    loadFile(in);

    IBitStream bitin(in);
    if (!bitin)
        throw std::exception();

    readAddInfo(in, bitin);

    outputDecodedText(bitin, out);

    printStatistics();
}

void HuffmanArchiver::readAddInfo(std::istream &in, IBitStream &bitin) {
    in.read(reinterpret_cast<char *>(&sh.add_size), sizeof(sh.add_size));
    sh.input_size -= sh.add_size;
    in.read(reinterpret_cast<char *>(&sh.decoded_text_size), sizeof(sh.decoded_text_size));

    uint16_t symbols_count;
    in.read(reinterpret_cast<char *>(&symbols_count), sizeof(symbols_count));
    std::vector<std::pair<uint8_t, uint8_t >> symbol_to_codelength(symbols_count); // fst - letter, snd - length of code

    for (int i = 0; i < symbols_count; ++i) {
        in.read(reinterpret_cast<char *>(&symbol_to_codelength[i].first), sizeof(uint8_t));
        in.read(reinterpret_cast<char *>(&symbol_to_codelength[i].second), sizeof(uint8_t));
    }

    std::streampos cur_iter = in.tellg();
    bitin.setIterPos(cur_iter);

    for (const auto &symbolANDcodelen : symbol_to_codelength) {
        std::string code;
        code.resize(symbolANDcodelen.second); // length of code
        bitin >> code;
        tree[code] = symbolANDcodelen.first; // symbol
    }

    bitin.clear();
}

void HuffmanArchiver::outputDecodedText(IBitStream &bitin, std::ostream &out) {
    if (!bitin || !out)
        throw std::exception();

    std::string code;
    uint8_t bit = 0;
    while (bitin && sh.decoded_text_size) {
        bitin >> bit;
        code.push_back(bit);
        if (tree.canDecoded(code)) {
            out.write(reinterpret_cast<const char *>(&tree[code]), sizeof(tree[code]));
            ++sh.output_size;
            code.resize(0);
            --sh.decoded_text_size;
        }
    }

    if (!bitin)
        throw std::exception();
}
