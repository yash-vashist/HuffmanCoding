#ifndef HUFFMAN_CODING
#define HUFFMAN_CODING
// Including all the required header files

#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <vector>
#include <bitset>

using namespace std;

//Defining Node Structure for huffman tree
class huffman_node {
    public:
    char ch;
    int freq;
    huffman_node* left, * right;

    huffman_node(char ch, int freq, huffman_node* left = nullptr, huffman_node* right = nullptr)
    :ch(ch), freq(freq), left(left), right(right){}
};

// Defining the interface
class huffmanCoding {
    public:
    huffmanCoding() = default;

    void compressFile(const string& input, const string& output);
    void decompressFile(const string& input, const string& output);

    private:

    huffman_node* buildHuffmanTree(map<char, int>& freq);
    void generateHuffmanCodes(huffman_node* root, string str, map<char, string>& huffmanCode);
    void deleteTree(huffman_node* root);
};

#endif