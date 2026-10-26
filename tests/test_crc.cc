#include "crc.h"
#include <cassert>
#include <string>

int main() {
    //C1: Standard value crc16
    assert(crc16("123456789") == 0x29B1);

    //C2: 4 digit, front 0 still remaining.
    assert(toHex4(0x29B1) == "29B1");
    assert(toHex4(0x00AF) == "00AF");

    //C3: completed payload p
    const std::string p = "00020101021226340016A0000000000000010110MRC0042TH15204581253037645406150.005802TH5914SOMTAM BANGKOK6007BANGKOK6304C871";    
    assert(hasValidCrc(p));
    assert(hasValidCrc("ABCF508"));

    //C4: copy of p, p remains the same
    std::string p_copy = p;
    p_copy[60] = '9';
    assert(!hasValidCrc(p_copy));

    //C5: payload is too short
    assert(!hasValidCrc(""));
    assert(!hasValidCrc("6304"));

    return 0;
}