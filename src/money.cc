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

//OPERATORS
        Money operator+(const Money &a, const Money &b) {
        if (a.currency() != b.currency())
            throw std::invalid_argument("different currency! cannot be added.");
        return Money(a.currency(), a.minorUnits() + b.minorUnits());
    }

    Money operator-(const Money &a, const Money &b) {
        if (a.currency() != b.currency())
            throw std::invalid_argument("different currency! cannot be subtracted.");
        return Money(a.currency(), a.minorUnits() - b.minorUnits());
    }

    bool operator==(const Money &a, const Money &b) {
        return a.currency() == b.currency() && a.minorUnits() == b.minorUnits(); 
    }

    std::strong_ordering operator<=>(const Money &a, const Money &b) {
        if (a.currency() != b.currency())
            throw std::invalid_argument("different currency! cannot be compared.");
        return a.minorUnits() <=> b.minorUnits();
    }

    std::ostream &operator<<(std::ostream &out, const Money &m) {
        //handling negative nominal
        int64_t minor = m.minorUnits();
        if (minor < 0)
            minor = -minor;
        
        if (minor < 10) {
            if (m.minorUnits() < 0)
                out << toCurrency(m.currency()) << " -0.0" << minor;
            else
                out << toCurrency(m.currency()) << " 0.0" << minor;
        } else if (minor < 100) {
            if (m.minorUnits() < 0)
                out << toCurrency(m.currency()) << " -0." << minor;
            else
                out << toCurrency(m.currency()) << " 0." << minor; 
        } else {

        int64_t difference = minor - minor / 100 * 100;

        if (difference == 0)
            out << toCurrency(m.currency()) << " " << m.minorUnits()/100 << ".00";
        else if (difference < 10)
            out << toCurrency(m.currency()) << " " << m.minorUnits()/100 << ".0" << difference;
        else
            out << toCurrency(m.currency()) << " " << m.minorUnits()/100 << "." << difference;
        }

        return out;
    }