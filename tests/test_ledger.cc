#include "ledger.h"
#include "transaction.h"
#include "money.h"
#include "currency.h"
#include <cassert>        // assert
#include <cstdint>        // std::int64_t
#include <stdexcept>      // catching std::invalid_argument
#include <string>         // std::string, std::to_string
#include <random>         // block 4 only: std::mt19937, distributions

int main() {
    Ledger led;
    led.addAccount("settle", Currency::THB, true);
    led.addAccount("alice", Currency::THB, false);
    led.addAccount("bob", Currency::THB, false);
    led.addAccount("sg", Currency::SGD, false);

    //L1: duplicate id
    bool threw = false;
    try {
        led.addAccount("alice", Currency::SGD, false);
    } catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);

    //L2: balance starter 0
    assert(led.balance("alice").minorUnits() == 0);

    //L3: settle -> alice 500
    led.post(Transaction{"t1", "settle", "alice", Money{Currency::THB, 500}});
    assert(led.balance("alice").minorUnits() == 500);
    assert(led.balance("settle").minorUnits() == -500);

    //L4: account DNE
    threw = false;
    try {
        led.post(Transaction{"t2", "alice", "fazli", Money{Currency::THB, 1}});
    } catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);

    //L5: same account
    threw = false;
    try {
        led.post(Transaction{"t3", "alice", "alice", Money{Currency::THB, 1}});
    } catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);

    //L6: different currency
    threw = false;
    try {
        led.post(Transaction{"t4", "alice", "sg", Money{Currency::THB, 1}});
    } catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);

    //L7 insufficient balance
    threw = false;
    try {
        led.post(Transaction{"t5", "alice", "bob", Money{Currency::THB, 900}});
    } catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);
    assert(led.balance("alice").minorUnits() == 500);
    assert(led.balance("bob").minorUnits() == 0);

    //L8 unknown balance
    threw = false;
    try {
        led.balance("fazli");
    } catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);

    //L9 amount <= 0
    threw = false;
    try {
        led.post(Transaction{"t6", "alice", "bob", Money{Currency::THB, -1}});
    } catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);
    assert(led.balance("alice").minorUnits() == 500);
    assert(led.balance("bob").minorUnits() == 0);

    threw = false;
    try {
        led.post(Transaction{"t6", "alice", "bob", Money{Currency::THB, 0}});
    } catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);
    assert(led.balance("alice").minorUnits() == 500);
    assert(led.balance("bob").minorUnits() == 0);

    return 0;
}