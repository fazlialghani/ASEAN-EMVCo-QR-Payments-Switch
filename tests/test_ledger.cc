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
        led.post(Transaction{"t7", "alice", "bob", Money{Currency::THB, 0}});
    } catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);
    assert(led.balance("alice").minorUnits() == 500);
    assert(led.balance("bob").minorUnits() == 0);

    //L10 100,000 transfers for checkinvariant()
    Ledger led2;
    led2.addAccount("settle", Currency::THB, true);
    led2.addAccount("a", Currency::THB, false);
    led2.addAccount("b", Currency::THB, false);
    led2.addAccount("c", Currency::THB, false);
    const std::string ids[] = {"settle", "a", "b", "c"};

    std::mt19937 rng{42}; //raw numbers
    std::uniform_int_distribution<int> pick{0, 3}; //from 4 accounts in ids.
    std::uniform_int_distribution<std::int64_t> units{1, 500}; //equally likely

    int rejected = 0;
    for (int i = 0; i < 100000; ++i) {
        Transaction tr{
            "r" + std::to_string(i),
            ids[pick(rng)],
            ids[pick(rng)],
            Money{Currency::THB, units(rng)}
        };
        try {
            led2.post(tr);
        } catch (const std::invalid_argument &) {
            ++rejected;
        }
        assert(led2.checkInvariant());
    }
    assert(rejected > 0);

    // L11: the same transaction id posted twice is applied only once.
    Ledger led3;
    led3.addAccount("settle", Currency::THB, true);
    led3.addAccount("alice", Currency::THB, false);

    led3.post(Transaction{"d1", "settle", "alice", Money{Currency::THB, 500}});
    led3.post(Transaction{"d1", "settle", "alice", Money{Currency::THB, 500}});

    assert(led3.balance("alice").minorUnits() == 500);
    assert(led3.balance("settle").minorUnits() == -500);
    assert(led3.checkInvariant());

    // L12: a failed transaction id is not recorded and can be retried.
    threw = false;
    try {
        led3.post(Transaction{"d2", "alice", "settle", Money{Currency::THB, 900}});
    } catch (const std::invalid_argument &) {
        threw = true;
    }
    assert(threw);

    led3.post(Transaction{"d2", "alice", "settle", Money{Currency::THB, 100}});
    assert(led3.balance("alice").minorUnits() == 400);
    return 0;
}