#include "scheme.h"     // PaymentScheme, PromptPayScheme, QrisScheme, PayNowScheme
#include "currency.h"   // Currency::THB, IDR, SGD in the asserts
#include <cassert>      // assert
#include <string>       // comparing name() and countryCode() with text
#include <memory>       // std::unique_ptr returned by makeScheme
#include <stdexcept>    // catching std::invalid_argument for "XX"

int main() {
    //S1.
    PromptPayScheme pp;
    const PaymentScheme &s = pp;
    assert(s.name() == "PromptPay");
    assert(s.currency() == Currency::THB);

    QrisScheme q;
    const PaymentScheme &s = q;
    assert(s.name() == "Qris");
    assert(s.currency() == Currency::IDR);

    PayNowScheme pn;
    const PaymentScheme &s = pn;
    assert(s.name() == "PromptPay");
    assert(s.currency() == Currency::SGD);

    //S2.
    auto th = makeScheme("TH");
    assert(th->name() == "PromptPay");
    assert(th->currency() == Currency::THB);

    auto id = makeScheme("iD");
    assert(id->name() == "QrisPay");
    assert(id->currency() == Currency::IDR);

    auto sg = makeScheme("SG");
    assert(sg->name() == "PayNow");
    assert(sg->currency() == Currency::SGD);

    bool threw = false;
    try {
        makeScheme("XX");
    } catch (const std::invalid_argument &) {
        assert(threw);
    }

    return 0;
}