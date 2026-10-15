#include "money.h"
#include <stdexcept>

//INITIALIZE
    Money::Money(Currency currency, std::int64_t minor) : currency_{currency}, minor_{minor} {}

    std::int64_t Money::minorUnits() const {
        return minor_;
    }

    Currency Money::currency() const {
        return currency_;
    }

    Money operator+(const Money &a, const Money&b) {
        if (a.currency() != b.currency())
            throw std::invalid_argument("different currency! cannot be added.");
        return Money(a.currency(), a.minorUnits() + b.minorUnits());
    }

    Money operator-(const Money &a, const Money&b) {
        if (a.currency() != b.currency())
            throw std::invalid_argument("different currency! cannot be subtracted.");
        return Money(a.currency(), a.minorUnits() - b.minorUnits());
    }