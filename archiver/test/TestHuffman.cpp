#include <iostream>
#include "doctest.h"
#include "Huffman.h"

TEST_CASE ("test_HuffmanNode_constructor") {
    std::unique_ptr<HuffmanNode> node = std::make_unique<HuffmanNode>(HuffmanNode(20,'a',true));
    CHECK_EQ(node->freq,20);
    CHECK_EQ(node->letter,'a');
    CHECK_EQ(node->is_leaf,true);
    CHECK_EQ(node->left, nullptr);
    CHECK_EQ(node->right, nullptr);
}

TEST_CASE ("test_HuffmanNode_node_constructor") {
    std::unique_ptr<HuffmanNode> node1 = std::make_unique<HuffmanNode>(HuffmanNode(130,'a',true));
    std::unique_ptr<HuffmanNode> node2 = std::make_unique<HuffmanNode>(HuffmanNode(20,'b',true));

    std::unique_ptr<HuffmanNode> res_node = std::make_unique<HuffmanNode>(std::move(node1),std::move(node2));

    CHECK_EQ(res_node->freq,150);
    CHECK_EQ(res_node->is_leaf, false);
    CHECK_EQ(res_node->left->freq,130);
    CHECK_EQ(res_node->right->freq,20);
    CHECK_EQ(res_node->left->letter,'a');
    CHECK_EQ(res_node->right->letter,'b');
    CHECK_EQ(res_node->left->is_leaf, true);
    CHECK_EQ(res_node->right->is_leaf, true);
}

TEST_CASE ("test_NodeComparer") {
    std::unique_ptr<HuffmanNode> node1 = std::make_unique<HuffmanNode>(HuffmanNode(130,'a',true));
    std::unique_ptr<HuffmanNode> node2 = std::make_unique<HuffmanNode>(HuffmanNode(20,'b',true));
    CHECK_LE(node2->freq,node1->freq);
}

TEST_CASE ("test_codeMap[]") {
    HuffmanTree tree;
    std::vector<uint8_t> symbols = {'a','b','c','d','e'};
    std::vector<std::vector<uint8_t>> codes(5);
    codes[0] = {1, 1};
    codes[1] = {0, 1, 1};
    codes[2] = {1, 0};
    codes[3] = {0, 1, 0, 1};
    codes[4] = {0, 1, 0, 0};

    uint8_t iter = 0;
    for (auto &symbol : symbols) {
        tree[symbol] = codes[iter++];
    }

    CHECK_EQ(codes[0], tree[symbols[0]]);
    CHECK_EQ(codes[1], tree[symbols[1]]);
    CHECK_EQ(codes[2], tree[symbols[2]]);
    CHECK_EQ(codes[3], tree[symbols[3]]);
    CHECK_EQ(codes[4], tree[symbols[4]]);
}

TEST_CASE ("test_decodeMap[]") {
    HuffmanTree tree;
    std::vector<uint8_t> symbols = {'a','b','c','d','e'};
    std::vector<std::string> codes(5);
    codes[0] = "11";
    codes[1] = "011";
    codes[2] = "10";
    codes[3] = "0101";
    codes[4] = "0100";

    uint8_t iter = 0;
    for (auto &code : codes) {
        tree[code] = symbols[iter++];
    }

    CHECK_EQ(symbols[0], tree[codes[0]]);
    CHECK_EQ(symbols[1], tree[codes[1]]);
    CHECK_EQ(symbols[2], tree[codes[2]]);
    CHECK_EQ(symbols[3], tree[codes[3]]);
    CHECK_EQ(symbols[4], tree[codes[4]]);
}

TEST_CASE ("test_Build") {
    std::vector<uint32_t> freqs(BYTE_ALPHABET_SIZE);

    // ======= abracadabra ============

    freqs['a'] = 5;
    freqs['b'] = 2;
    freqs['r'] = 2;
    freqs['c'] = 1;
    freqs['d'] = 1;

    std::vector<std::vector<uint8_t>> codes(BYTE_ALPHABET_SIZE);
    codes['a'] = {0};
    codes['b'] = {1, 0};
    codes['c'] = {1, 1, 0, 1};
    codes['d'] = {1, 1, 0, 0};
    codes['r'] = {1, 1, 1};

    HuffmanTree tree;
    tree.Build(freqs);

    for ( auto& x : tree['c'])
        std::cout << (int)x;
    std::cout << "\n";

    CHECK_EQ(tree['a'],codes['a']);
    CHECK_EQ(tree['b'],codes['b']);
    CHECK_EQ(tree['c'],codes['c']);
    CHECK_EQ(tree['d'],codes['d']);
    CHECK_EQ(tree['r'],codes['r']);
}