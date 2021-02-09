#include "crc32csum.h"

#include <iostream>
#include <fstream>
#include <cstring>

// const int32_t BUFFER_SIZE = 64;

// template <typename I> std::string n2hexstr(I w, size_t hex_len = sizeof(I)<<1) {
//     static const char* digits = "0123456789abcdef";
//     std::string rc(hex_len,'0');
//     for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
//         rc[i] = digits[(w>>j) & 0x0f];
//     return rc;
// }

// uint32_t compute_crc32c_checksum(std::string filepath) {

//     int32_t currSize = 0;
//     int32_t totalSize = 0;
//     int32_t extraSize = 0;
//     uint32_t crc = 0;

//     typedef unsigned char uint8;
//     uint8 *buff = new uint8[BUFFER_SIZE];

//     // std::ifstream source("../crc32c-checksum/file.txt", std::ios::in|std::ios::binary|std::ios::ate);
//     std::ifstream source(filepath, std::ios::in|std::ios::binary);

//     if(source.fail()) {
//         std::cerr << "File failed to open" << std::endl;
//         return 0;
//     }

//     source.seekg (0, std::ios::end);
//     totalSize = source.tellg();
//     source.seekg (0, std::ios::beg);

//     while (!source.eof()) {
//         extraSize = totalSize - currSize;

//         memset(buff, 0x00, BUFFER_SIZE);

//         if (extraSize >= BUFFER_SIZE) {
//             source.read((char*)buff, BUFFER_SIZE);
//             crc = crc32c_append(crc, buff, BUFFER_SIZE);
//         } else {
//             source.read((char*)buff, extraSize);
//             crc = crc32c_append(crc, buff, extraSize);
//             break;
//         }

//         currSize = currSize + BUFFER_SIZE;
//     }

//     source.close();
//     delete[] buff;

//     return crc;
// }

// bool is_good(std::string filepath) {
//     std::ifstream file_to_read(filepath);
//     bool res = file_to_read.good();
//     file_to_read.close();
//     return res;
// }

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cerr << "Usage: crc32csum <file>[ <another_file>]..." << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {

        if (is_good(argv[i])) {

            uint32_t crc = compute_crc32c_checksum(argv[i]);

            if (crc != 0) {
                std::cout << n2hexstr(crc) << "\t" << argv[i] << std::endl;
            } else {
                std::cerr << "Unexpected error reading file: " << argv[i] << std::endl;
                return 1;
            }

        } else {
            std::cerr << "Cannot open file: " << argv[i] << std::endl;
            return 1;
        }
    }

    return 0;
}
