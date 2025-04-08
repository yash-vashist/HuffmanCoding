#include "HuffmanCoding.h"

int main() {
    string input = "input.txt";
    string output = "compressed.huff";
    string decompressedFile = "decompressed.txt";

    huffmanCoding dummy;

    // compressing the input file and storing it in output file
    dummy.compressFile(input, output);

    // decompressing the output file and storing it into decompressed file
    dummy.decompressFile(output, decompressedFile);

    cout << "" << endl;

    return 0;
}