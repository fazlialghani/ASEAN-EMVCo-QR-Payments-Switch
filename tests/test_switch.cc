#include "switch.h"       // parseAmount, processPayment
#include "ledger.h"       // Ledger
#include "transaction.h"  // Transaction for funding the tourist
#include "money.h"        // Money
#include "currency.h"     // Currency::THB
#include <cassert>        // assert
#include <stdexcept>      // catching std::invalid_argument
#include <string>         // payload strings

int main() {
    //S1: valid
    assert(parseAmount("150.00") == 15000);
    assert(parseAmount("7") == 700);
    assert(parseAmount("0.5") == 50);

    //S2: invalid -> throw
    const std::string cases[] = {"1.234", "", "1,5", "abc"};
    int bad = 0;
    for (std::size_t i = 0; i < 4; i++) {
        try {
            parseAmount(cases[i]);
        } catch (const std::invalid_argument &) {
            ++bad;
        }
    }
    assert(bad == 4);

    ///// end-to-end test, complete payload
    const std::string p = "00020101021226340016A0000000000000010110MRC0042TH15204581253037645406150.005802TH5914SOMTAM BANGKOK6007BANGKOK6304C871";
    Ledger led;
    led.addAccount("settle", Currency::THB, true);
    led.addAccount("tourist", Currency::THB, false);
    led.addAccount("somtam", Currency::THB, false);
    led.post(Transaction{"f1", "settle", "tourist", Money{Currency::THB, 50000}});

    // S3: one payment moves 150.00 THB from tourist to somtam
    processPayment(led, "p1", p, "tourist", "somtam");
    assert(led.balance("somtam").minorUnits() == 15000);
    assert(led.balance("tourist").minorUnits() == 35000);

    // S4: the same transaction id again is ignored
    processPayment(led, "p1", p, "tourist", "somtam");
    assert(led.balance("somtam").minorUnits() == 15000);
    assert(led.balance("tourist").minorUnits() == 35000);

    // S5: a corrupted payload is rejected and changes nothing
    std::string broken = p;
    broken[60] = '9';
    bool threw = false;
    try {
        processPayment(led, "p2", broken, "tourist", "somtam");
    } catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);
    assert(led.balance("somtam").minorUnits() == 15000);
    assert(led.balance("tourist").minorUnits() == 35000);

    return 0;
}

