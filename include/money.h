#pragma once
#include <cstdint>
#include <stdexcept>
#include "currency.h"
#include <compare>
#include <ostream>

class Money {
    private:
        Currency currency_;
        std::int64_t minor_; //iDR: SEN, SGD: CENT, THB: SATANG (100) for simplification.
    public:
    //ctor
        Money(Currency currency, std::int64_t minor);
    //getter()
        std::int64_t minorUnits() const;
        Currency currency() const;
    //friend (give a permission to access the private member outside of class)
        friend std::ostream &operator<<(std::ostream& out, const Money &m);
};

Money operator+(const Money &a, const Money &b);
Money operator-(const Money &a, const Money &b);
bool operator==(const Money &a, const Money &b);
std::strong_ordering operator<=>(const Money &a, const Money &b);