#include <cassert>
#include <sstream>
#include <stdexcept>
#include "money.h"

int main() {
    Money a{Currency::THB, 500};
    Money b{Currency::THB, 500};
    Money c{Currency::THB, 700};
    Money d{Currency::IDR, 500};

    //T1. same currency
    assert(a == b);
    assert(!(a == c));

    //T2. diff currency
    assert(!(a == d));

    //T3. comparison operator
    assert(a < c);
    assert(a <= b);
    assert(a >= b);
    assert(c > b);

    //T4. diff currency => throw
    bool threw = false;
    try {
        bool r = (a < d);
        (void) r;
    }
    catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);

    //T5. Print
    std::ostringstream os;
    os << a;
    assert(os.str() == "THB 5.00");

    os.str("");
    os << Money{Currency::IDR, 5};
    assert(os.str() == "IDR 0.05");

    os.str("");
    os << Money{Currency::IDR, -7};
    assert(os.str() == "IDR -0.07");

    os.str("");
    os << Money{Currency::THB, 15000};
    assert(os.str() == "THB 150.00");

    os.str("");
    os << Money{Currency::SGD, 105};
    assert(os.str() == "SGD 1.05");

    os.str("");
    os << Money{Currency::SGD, 1234};
    assert(os.str() == "SGD 12.34");

    os.str("");
    os << Money{Currency::SGD, -150};
    assert(os.str() == "SGD -1.50");

    return 0;
}

