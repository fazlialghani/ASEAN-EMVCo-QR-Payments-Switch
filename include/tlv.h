#pragma once
#include <string>

struct TlvField {           // header: tag and length
    std::string tag;        // [_ _] [_ _] [....]
    std::string value;      //  tag  length value
};

bool parseField(const std::string &payload, std::size_t pos, TlvField &field);
