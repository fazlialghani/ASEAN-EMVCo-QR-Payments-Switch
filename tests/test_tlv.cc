#include <cassert>
#include "tlv.h"

int main() {
    const std::string p = "000201010212";
    TlvField f;

    //T1 first field
    assert(parseField(p, 0, f));
    assert(f.tag == "00");
    assert(f.value == "01");

    //T2 second field
    assert(parseField(p, 6, f));
    assert(f.tag == "01");
    assert(f.value == "12");

    //T3 cut value
    assert(!parseField("0002", 0, f));

    //T4 cut header
    assert(!parseField("00", 0, f));

    return 0;
}