#include "crc.h"
#include <cstdint>
#include <string>

std::uint16_t crc16(const std::string &data)
{
    //computes the CRC-16/CCITT-FALSE checksum of a string
    //(init 0xFFFF, poly 0x1021), so any change to the data
    //produces a different 16-bit value.
    std::uint16_t crc = 0xFFFF;

    for (unsigned char c : data) {
        crc ^= (c << 8);
        for (int i = 0; i < 8; ++i) {
            if (crc & 0x8000)
                crc = static_cast<std::uint16_t>((crc << 1) ^ 0x1021);
            else
                crc = static_cast<std::uint16_t>(crc << 1);
        }
    }
    return crc;
}

std::string toHex4(std::uint16_t v)
{
    //converts a 16-bit value into exactly 4 uppercase hex characters,
    //keeping leading zeros (0x00AF → "00AF").
    const std::string digits = "0123456789ABCDEF";
    std::string out;
    out.push_back(digits[(v >> 12) & 0xF]);
    out.push_back(digits[(v >> 8) & 0xF]);
    out.push_back(digits[(v >> 4) & 0xF]);
    out.push_back(digits[v & 0xF]);

    return out;
}

bool hasValidCrc(const std::string &p)
{
    //returns true if the last 4 characters of the payload equal toHex4(crc16(...))
    //of everything before them, and false if the payload is too short or the values don’t match.
    if (p.size() < 4)
        return false;
    
    std::string body = p.substr(0, p.size() - 4);
    std::string tail = p.substr(p.size() - 4);

    return toHex4(crc16(body)) == tail;

}