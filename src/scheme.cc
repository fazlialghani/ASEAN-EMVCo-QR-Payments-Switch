#include "scheme.h"     // PaymentScheme, the three schemes, makeScheme
#include "currency.h"   // Currency::THB, IDR, SGD in the asserts
#include <cassert>      // assert
#include <memory>       // std::unique_ptr returned by makeScheme
#include <stdexcept>    // catching std::invalid_argument for unknown codes
#include <string>       // comparing name() and countryCode() with text

std::unique_ptr<PaymentScheme> makeScheme(const std::string &country) {
    if (country == "TH")
        return std::make_unique<PromptPayScheme>();
    if (country == "ID")
        return std::make_unique<QrisScheme>();
    if (country == "SG")
        return std::make_unique<PayNowScheme>();

    throw std::invalid_argument("makeScheme: unknown country '" + country + "'");
}