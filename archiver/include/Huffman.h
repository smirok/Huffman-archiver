#ifndef HW_03_HUFFMAN_H
#define HW_03_HUFFMAN_H

#include <memory>
#include <unordered_map>
#include <vector>
#include <climits>

constexpr uint16_t BYTE_ALPHABET_SIZE = 1 << CHAR_BIT;

// =============== NODE =========================

struct HuffmanNode {
    HuffmanNode(uint32_t freq, uint8_t lit, bool is_leaf_);

    HuffmanNode(std::unique_ptr<HuffmanNode> first, std::unique_ptr<HuffmanNode> second);

    uint32_t freq;
    uint8_t letter;
    std::unique_ptr<HuffmanNode> left = nullptr, right = nullptr;
    bool is_leaf;
};

struct NodeComparer {
    bool operator()(const std::unique_ptr<HuffmanNode> &fst,
                    const std::unique_ptr<HuffmanNode> &snd) const;
};

// ================ TREE ========================

class HuffmanTree {
public:
    void Build(std::vector<uint32_t> &freqs) noexcept;

    std::vector<uint8_t> &operator[](uint8_t symbol) noexcept;

    uint8_t &operator[](const std::string &code) noexcept;

    bool canDecoded(const std::string &code) const noexcept;

private:
    void fillCodeMap(std::unique_ptr<HuffmanNode> cur_node, std::vector<uint8_t> &cur_code) noexcept;

    void generateCodes() noexcept;

    std::unordered_map<uint8_t, std::vector<uint8_t>> code_map;
    std::unordered_map<std::string, uint8_t> decode_map;
    std::unique_ptr<HuffmanNode> root;
};

#endif //HW_03_HUFFMAN_H
