#include "tlv.h"
#include <string>
#include <cstddef>
#include <vector>
#include <utility>

namespace
{
    bool isDigit(char c) {
    //checks whether a single character is '0' through '9', so a field
    //length is never computed from arbitrary characters.

        //true if c in '01234..9'
        return c >= '0' && c <= '9';
    }
}

bool parseField(const std::string &payload, std::size_t pos, TlvField &field)
{
    //reads one TLV field (2-char tag, 2-digit length, then the value) starting at
    //a given position, and returns false if that field is malformed or truncated.

    //invalid TLV.
    if (pos + 4 > payload.size())
        return false;
    
    //take the tag.
    field.tag = payload.substr(pos, 2);

    //read the length.
    if (!(isDigit(payload[pos + 2]) && isDigit(payload[pos + 3])))
        return false;

    std::size_t len = static_cast<std::size_t>((payload[pos + 2] - '0') * 10 + (payload[pos + 3] - '0'));

    //cut value.
    if (pos + 4 + len > payload.size())
        return false;
    
    //take the value.
    field.value = payload.substr(pos + 4, len);
    return true;
}

bool parse(const std::string &payload, std::vector<TlvField> &fields)
{
    //calls parseField repeatedly from the start to the end of the payload,
    //collects every field, and only fills the output once the whole payload has proven valid.

    std::vector<TlvField> tmp;
    std::size_t pos = 0;

    while (pos < payload.size()) {
        TlvField f;
        if (!parseField(payload, pos, f))
            return false;
        tmp.push_back(f);
        pos += 4 + f.value.size();
    }

    fields = std::move(tmp);

    return true;
}

bool findTag(const std::vector<TlvField> &fields, const std::string &tag, TlvField &out)
{
    //looks up the field with a given tag (for example "59" for the merchant name)
    //in the list produced by parse.

    for (std::size_t i = 0; i < fields.size(); ++i) {
        const TlvField &f = fields[i];

        if (f.tag == tag) {
            out = f;
            return true;
        }
    }

    return false;
}

