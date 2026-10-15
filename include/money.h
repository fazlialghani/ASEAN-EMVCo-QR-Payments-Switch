#pragma once
#include <cstdint>
#include <stdexcept>
#include "currency.h"

class Money {
    private:
        Currency currency_;
        std::int64_t minor_; //iDR: SEN, SGD: CENT, THB: SATANG (100) for simplification.
    public:
        Money(Currency currency, std::int64_t minor);
        std::int64_t minorUnits() const;
        Currency currency() const;
};

Money operator+(const Money &a, const Money&b);
Money operator-(const Money &a, const Money&b);