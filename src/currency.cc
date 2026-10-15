#include "currency.h"

std::string toCurrency(Currency c) {
    switch (c) {
        case Currency::IDR:
            return "IDR";
        case Currency::THB:
            return "THB";
        case Currency::SGD:
            return "SGD";
    }
    return "Unknown";
}
