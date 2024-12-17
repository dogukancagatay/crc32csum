#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "crc32csum.h"

#define NUM_TEST_CASES 4

namespace {
class TemporaryFile {
  public:
    TemporaryFile() : path_(std::filesystem::temp_directory_path() / std::tmpnam(nullptr)) {}
    ~TemporaryFile() { std::filesystem::remove(path_); }
    const std::filesystem::path &path() const { return path_; }

    void add_content(const std::string &content) {
        std::ofstream file(path_);
        file << content;
        file.close();
    }

  private:
    std::filesystem::path path_;
};
}

void assert(std::string test_name, std::string actual, std::string expected) {
    if (actual == expected) {
        std::cout << test_name << "\t" << "PASS" << std::endl;
    } else {
        std::cout << test_name << "\t" << "FAIL" << std::endl;
        abort();
    }
}

template <typename I> std::string n2hexstr(I w, size_t hex_len = sizeof(I) << 1) {
    static const char *digits = "0123456789abcdef";
    std::string rc(hex_len, '0');
    for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
        rc[i] = digits[(w >> j) & 0x0f];
    return rc;
}

void test_non_existent_file() {
    try {
        uint32_t crc = compute_crc32c_checksum("non_existent_file.txt");
    } catch (const std::invalid_argument &e) {
        assert(__func__, e.what(), "Failed to read: non_existent_file.txt");
    }
}

void test_empty_file() {
    TemporaryFile temp_file;
    {
        std::ofstream file(temp_file.path());
        file.close();
    }

    uint32_t crc = compute_crc32c_checksum(temp_file.path().string());
    std::cout << __func__ << ": " << n2hexstr(crc) << std::endl;
    assert(__func__, n2hexstr(crc), "00000000");
}

void test_single_char_file() {
    TemporaryFile temp_file;
    temp_file.add_content("A");
    uint32_t crc = compute_crc32c_checksum(temp_file.path().string());
    std::cout << __func__ << ": " << n2hexstr(crc) << std::endl;
    assert(__func__, n2hexstr(crc), "e16dcdee");
}

void test_oneline_text_file() {
    TemporaryFile temp_file;
    temp_file.add_content("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
    uint32_t crc = compute_crc32c_checksum(temp_file.path().string());
    std::cout << __func__ << ": " << n2hexstr(crc) << std::endl;
    assert(__func__, n2hexstr(crc), "6c7d6adf");
}

void test_multiline_text_file() {
    TemporaryFile temp_file;
    temp_file.add_content("Lorem\nipsum\ndolor sit amet,\nconsectetur\nadipiscing\nelit.");
    uint32_t crc = compute_crc32c_checksum(temp_file.path().string());
    std::cout << __func__ << ": " << n2hexstr(crc) << std::endl;
    assert(__func__, n2hexstr(crc), "d59c1bb5");
}

int main(int argc, char **argv) {
    test_non_existent_file();
    test_empty_file();
    test_single_char_file();
    test_oneline_text_file();
    test_multiline_text_file();
    return 0;
}
