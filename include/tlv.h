#pragma once
#include <string>
#include <vector>

struct TlvField {           // header: tag and length
    std::string tag;        // [_ _] [_ _] [....]
    std::string value;      //  tag  length value
};

bool parseField(const std::string &payload, std::size_t pos, TlvField &field);
bool parse(const std::string &payload, std::vector<TlvField> &fields);
bool findTag(const std::vector<TlvField> &fields, const std::string &tag, TlvField &out);