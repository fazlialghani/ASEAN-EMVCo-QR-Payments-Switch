#include "scheme.h"     // PaymentScheme, PromptPayScheme, QrisScheme, PayNowScheme
#include "currency.h"   // Currency::THB, IDR, SGD in the asserts
#include <cassert>      // assert
#include <string>       // comparing name() and countryCode() with text
#include <memory>       // std::unique_ptr returned by makeScheme
#include <stdexcept>    // catching std::invalid_argument for "XX"

int main() {
    //S1.
    PromptPayScheme pp;
    const PaymentScheme &s1 = pp;
    assert(s1.name() == "PromptPay");
    assert(s1.currency() == Currency::THB);

    QrisScheme q;
    const PaymentScheme &s2 = q;
    assert(s2.name() == "Qris");
    assert(s2.currency() == Currency::IDR);

    PayNowScheme pn;
    const PaymentScheme &s3 = pn;
    assert(s3.name() == "PayNow");
    assert(s3.currency() == Currency::SGD);

    //S2.
    auto th = makeScheme("TH");
    assert(th->name() == "PromptPay");
    assert(th->currency() == Currency::THB);

    auto id = makeScheme("ID");
    assert(id->name() == "Qris");
    assert(id->currency() == Currency::IDR);

    auto sg = makeScheme("SG");
    assert(sg->name() == "PayNow");
    assert(sg->currency() == Currency::SGD);

    bool threw = false;
    try {
        makeScheme("XX");
    } catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);

    return 0;
}