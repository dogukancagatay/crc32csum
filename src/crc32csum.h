#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "crc32c/crc32c.h"

uint32_t compute_crc32c_checksum(std::string filepath) {
    std::ifstream source(filepath, std::ios::binary);

    if (!source.good() or source.fail()) {
        throw std::invalid_argument("Failed to read: " + filepath);
    }

    const size_t BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];
    uint32_t crc = 0;

    while (source.read(buffer, BUFFER_SIZE)) {
        crc = crc32c::Extend(crc, reinterpret_cast<const uint8_t *>(buffer), source.gcount());
    }

    if (source.gcount() > 0) {
        crc = crc32c::Extend(crc, reinterpret_cast<const uint8_t *>(buffer), source.gcount());
    }

    source.close();
    return crc;
}
