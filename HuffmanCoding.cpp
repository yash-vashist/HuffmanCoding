#include "HuffmanCoding.h"

huffman_node* huffmanCoding :: buildHuffmanTree(map<char, int>& freq) {
    //Making custom comparator Functor using Lambda functions
    auto cmp = [](huffman_node* first, huffman_node* second){
        return first -> freq > second -> freq;
    };

    priority_queue<huffman_node*, vector<huffman_node*>, decltype(cmp)> pq(cmp);

    for(auto pair : freq) {
        pq.push(new huffman_node(pair.first, pair.second));
    }

    while(pq.size() != 1) {
        huffman_node* left = pq.top();pq.pop();
        huffman_node* right = pq.top();pq.pop();

        int sumFreq = left -> freq + right -> freq;
        pq.push(new huffman_node('\0', sumFreq, left, right));
    }

    return pq.top();
}

void huffmanCoding :: generateHuffmanCodes(huffman_node* root, string str, map<char, string>& huffmanCode) {
    if(root == nullptr)
        return;
    
    if(root -> left == nullptr && root -> right == nullptr)
        huffmanCode[root -> ch] = str;

    generateHuffmanCodes(root -> left, str + "0", huffmanCode);
    generateHuffmanCodes(root -> right, str + "1", huffmanCode);
}

void huffmanCoding :: compressFile(const string& input, const string& output) {
    ifstream in(input, ios :: binary);
    if(!in.is_open()) {
        cerr << "Could not open the input file. " << endl;
        return;
    }

    string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    // Calculating frequencies
    map<char, int> freq;
    for(char ch : data) {
        freq[ch]++;
    }

    //Building Huffman Tree
    huffman_node* root = buildHuffmanTree(freq);

    // Generating Huffman Codes
    map<char, string> huffmanCode;
    generateHuffmanCodes(root, "", huffmanCode);

    //Encoding the tree
    string encoded = "";
    for(char ch : data) {
        encoded += huffmanCode[ch];
    }

    ofstream out(output, ios :: binary);
    if(!out.is_open()) {
        cerr << "Could not open the output file. " << endl;
    }

    //Writing the frequency table size and table to the compressed file
    size_t freqSize = freq.size();
    out.write(reinterpret_cast<char*> (&freqSize), sizeof(freqSize));
    for(auto pair : freq) {
        out.write(&pair.first, sizeof(pair.first));
        out.write(reinterpret_cast<char*> (&pair.second), sizeof(pair.second));
    }

    //Writing the encoded data length and data as binary
    size_t encodedLength = encoded.length();
    out.write(reinterpret_cast<char*> (&encodedLength), sizeof(encodedLength));
    for(size_t i = 0; i < encodedLength; i += 8) {
        bitset<8> bits(encoded.substr(i, 8));
        unsigned char byte = static_cast<unsigned char>(bits.to_ulong());
        out.write(reinterpret_cast<char*> (&byte), sizeof(byte));
    }

    out.close();
    deleteTree(root);
}

void huffmanCoding :: decompressFile(const string& input, const string& output) {
    ifstream in(input, ios :: binary);
    if(!in.is_open()) {
        cerr << "Could not open the input file. " << endl;
        return;
    }

    //Reading the frequency table and it's size
    size_t freqSize;
    in.read(reinterpret_cast<char*> (&freqSize), sizeof(freqSize));
    map<char, int> freq;
    for(size_t i = 0; i < freqSize; i++) {
        char ch;
        int frequency;
        in.read(&ch, sizeof(ch));
        in.read(reinterpret_cast<char*> (&frequency), sizeof(frequency));
        freq[ch] = frequency;
    }

    //Rebuilding the Huffman Tree
    huffman_node* root = buildHuffmanTree(freq);

    //Reading the encoded string and it's length
    size_t encodedLength;
    in.read(reinterpret_cast<char*> (&encodedLength), sizeof(encodedLength));
    string encoded = "";
    for(size_t i = 0; i < (encodedLength+7)/8; i++) {
        unsigned char byte;
        in.read(reinterpret_cast<char*> (&byte), sizeof(byte));
        bitset<8> bits(byte);
        encoded += bits.to_string();
    }
    encoded = encoded.substr(0, encodedLength);

    in.close();

    ofstream out(output, ios :: binary);
    if(!out.is_open()) {
        cerr << "Could not open the output file. " << endl;
        return;
    }

    //Decoding the encoded string
    huffman_node* curr = root;
    string decoded = "";
    for(char bit : encoded) {
        curr = (bit == '0')?curr -> left : curr -> right;

        if(curr -> left == nullptr && curr -> right == nullptr) {
            decoded += curr -> ch;
            curr = root;
        }
    }

    out << decoded;
    out.close();
    deleteTree(root);
}

void huffmanCoding :: deleteTree(huffman_node* root) {
    if(root == nullptr)
        return;
    
    deleteTree(root -> left); // Deleting left tree recursively
    deleteTree(root -> right); // Deleting right tree recursively
}
