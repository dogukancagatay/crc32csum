#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cassert>

#include "crc32csum.h"

#define NUM_TEST_CASES 4

using namespace std;

void create_test_file1() {

    ofstream file("./test_file1.txt");

    file << "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";

    file.close();

}

void create_test_file2() {

    ofstream file("./test_file2.txt");

    file << "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    file << " Integer dignissim velit vestibulum neque auctor vehicula.";
    file << " Praesent odio est, auctor vel luctus ac, dictum ac sem. Phasellus pharetra sapien eu laoreet scelerisque.";
    file << " In imperdiet consectetur diam sit amet fermentum. Sed eu luctus sapien.";
    file << " Vestibulum accumsan ut risus vel cursus. Proin id mattis enim.";
    file << " Pellentesque eu dui sit amet sem vestibulum vehicula vel sed urna.";

    file.close();

}

void create_test_file3() {

    ofstream file("./test_file3.txt");

    file << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

    file.close();

}

void create_test_file4() {

    ofstream file("./test_file4.txt");

    file << "A";

    file.close();

}


int main(int argc, char **argv) {

    create_test_file1();
    create_test_file2();
    create_test_file3();
    create_test_file4();

    string file_list[NUM_TEST_CASES] { "./test_file1.txt", "./test_file2.txt", "./test_file3.txt", "./test_file4.txt" };
    string result_list[NUM_TEST_CASES] { "6c7d6adf", "830eb408", "8051b9cb", "e16dcdee" };

    for (size_t i = 0; i < NUM_TEST_CASES; i++) {

        uint32_t crc = compute_crc32c_checksum(file_list[i]);

        // cout << file_list[i] << ": " << n2hexstr(crc) << endl;

        assert(n2hexstr(crc) == result_list[i]);

        remove(file_list[i].c_str());

    }

    cout << "Tests completed successfully" << endl;

    return 0;
}
