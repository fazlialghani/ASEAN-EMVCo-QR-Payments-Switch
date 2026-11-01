#include "crc.h"        // crc16, toHex4
#include <iostream>     // std::cout, std::cerr
#include <string>       // std::string

// Appends the EMVCo CRC field (tag 63, length 04, and the computed CRC) to
//a payload body, so the output passes hasValidCrc.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "usage: make_payload <body>\n"; 
        return 1;
    }
    std::string body = std::string(argv[1]) + "6304"; //standard tag & length of CRC 63 04
    std::cout << body + toHex4(crc16(body));

    return 0;
}