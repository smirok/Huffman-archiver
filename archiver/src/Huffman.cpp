#include "Huffman.h"
#include <algorithm>
#include <set>

HuffmanNode::HuffmanNode(uint32_t freq_, uint8_t lit, bool is_leaf_) :
        freq(freq_),
        letter(lit),
        is_leaf(is_leaf_) {}

HuffmanNode::HuffmanNode(std::unique_ptr<HuffmanNode> first,
                         std::unique_ptr<HuffmanNode> second) :
        freq(first->freq + second->freq),
        left(std::move(first)),
        right(std::move(second)),
        is_leaf(false) {}

bool NodeComparer::operator()(const std::unique_ptr<HuffmanNode> &fst,
                              const std::unique_ptr<HuffmanNode> &snd) const {
    return (fst->freq <= snd->freq);
}

void HuffmanTree::Build(std::vector<uint32_t> &freqs) noexcept {
    std::set<std::unique_ptr<HuffmanNode>, NodeComparer> tree;

    for (uint16_t i = 0; i < BYTE_ALPHABET_SIZE; ++i) {
        if (freqs[i])
            tree.insert(
                    std::make_unique<HuffmanNode>(
                            HuffmanNode(freqs[i], i, true)
                    )
            );
    }

    if (tree.empty())
        return;

    if (tree.size() == 1) {
        root = std::move(tree.extract(tree.begin()).value());
        code_map[root->letter].push_back(0);
        return;
    }

    while (tree.size() > 1) {
        std::unique_ptr<HuffmanNode> temp_node1 = std::move(tree.extract(tree.begin()).value());
        std::unique_ptr<HuffmanNode> temp_node2 = std::move(tree.extract(tree.begin()).value());

        tree.insert(std::make_unique<HuffmanNode>(HuffmanNode(std::move(temp_node1), std::move(temp_node2))));
    }

    root = std::move(tree.extract(tree.begin()).value());

    generateCodes();
}

void HuffmanTree::fillCodeMap(std::unique_ptr<HuffmanNode> cur_node, std::vector<uint8_t> &cur_code) noexcept {
    if (cur_node->is_leaf) {
        code_map[cur_node->letter] = cur_code;
        return;
    }

    cur_code.push_back(0);
    fillCodeMap(std::move(cur_node->left), cur_code);
    cur_code.pop_back();
    cur_code.push_back(1);
    fillCodeMap(std::move(cur_node->right), cur_code);
    cur_code.pop_back();
}

void HuffmanTree::generateCodes() noexcept {
    std::vector<uint8_t> code;
    fillCodeMap(std::move(root), code);
}

std::vector<uint8_t> &HuffmanTree::operator[](uint8_t c) noexcept {
    return code_map[c];
}

uint8_t &HuffmanTree::operator[](const std::string &code) noexcept {
    return decode_map[code];
}

bool HuffmanTree::canDecoded(const std::string &code) const noexcept {
    return (decode_map.find(code) != decode_map.end());
}