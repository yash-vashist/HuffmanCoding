
# Huffman Coding Compression Tool



## Description
Developed a data compression tool using the Huffman coding algorithm, capable of compressing and decompressing text files.
## Tech Stack
* C++
*  Standard Template Library (STL)
* GCC/G++
* Visual Studio Code
## Features
* Implemented the Huffman coding algorithm to generate prefix codes for characters based on their frequencies.
* Used STL's priority queue to manage the construction of the Huffman tree.
* Leveraged STL's map for efficient frequency counting of characters in the input text.
* Handled file I/O operations to read the input text file, output the compressed file, and manage the decompression process.
* Ensured robustness and efficiency through extensive testing and validation.
##  Prerequisites
* C++ compiler (GCC/G++ or any other standard C++ compiler).
* Visual Studio Code or any other preferred IDE/editor.
## Installation

1. Clone the repository: 

```bash
  git clone https://github.com/yash-vashist/HuffmanCoding
  cd huffman-coding-compression-tool

```
2. Build the project: 
```bash
  g++ -o main main.cpp HuffmanCoding.cpp
```
3. Run the executables:
```bash
  ./main
```

    
## File Structure
* huffman_compression.cpp: Main source code implementing the * * Huffman coding algorithm.
* README.md: Project documentation.
* input.txt: Sample input text file for testing.
* compressed.huff: Sample compressed output file.
* decompressed.txt: Sample decompressed output file.
