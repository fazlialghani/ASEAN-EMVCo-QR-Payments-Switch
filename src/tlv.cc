#include "tlv.h"


bool parseField(const std::string &payload, std::size_t pos, TlvField &field) {
    //invalid TLV.
    if (pos + 4 > payload.size())
        return false;
    
    //take the tag.
    field.tag = payload.substr(pos, 2);

    //read the length.
    int len = (payload[pos + 2] - '0') * 10 + (payload[pos + 3] - '0');

    //cut value.
    if (pos + 4 + len > payload.size())
        return false;
    
    //take the value.
    field.value = payload.substr(pos + 4, len);
    return true;
}