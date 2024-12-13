#include <cstring>
#include <fstream>
#include <iostream>

#include "crc32csum.h"

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cerr << "Usage: crc32csum <file>[ <another_file>]..." << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        try {
            uint32_t crc = compute_crc32c_checksum(argv[i]);
            std::cout << crc << "\t" << argv[i] << std::endl;
        } catch (const std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
            continue;
        }
    }

    return 0;
}
