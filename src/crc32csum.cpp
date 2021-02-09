#include "crc32csum.h"

#include <iostream>
#include <fstream>
#include <cstring>

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
