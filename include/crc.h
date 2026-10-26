#pragma once
#include <cstdint>
#include <string>

std::uint16_t crc16(const std::string &data);
std::string toHex4(std::uint16_t v);
bool hasValidCrc(const std::string &payload);