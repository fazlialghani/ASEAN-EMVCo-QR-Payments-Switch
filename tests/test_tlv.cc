#include <cassert>
#include "tlv.h"

int main() {
    const std::string p = "000201010212";
    const std::string p2 = "00020101021226340016A0000000000000010110MRC0042TH15204581253037645406150.005802TH5914SOMTAM BANGKOK6007BANGKOK6304C871";
    std::vector<TlvField> fs;
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

    //T5 non-digit length
    assert(!parseField("000/AB", 0, f));
    assert(!parseField("00/0AB", 0, f));

    //T6 parse bangkok, success
    assert(parse(p2, fs));
    assert(fs.size() == 10);
    assert(fs[4].value == "764");
    assert(fs[5].value == "150.00");
    assert(fs[6].value == "TH");

    //T7 invalid length
    assert(!parse("0002010", fs));

    //T8 original field unchanged after the parse failed.
    std::vector<TlvField> fs_1{TlvField{"99", "SG"}}; //use 99 for distinguishing the before and after of tag.
    assert(!parse("0002010", fs_1));
    assert(fs_1.size() == 1);
    assert(fs_1[0].tag == "99");

    //T9 find tag
    assert(findTag(fs, "59", f));
    assert(f.value == "SOMTAM BANGKOK");
    assert(!findTag(fs, "50", f));

    return 0;
}