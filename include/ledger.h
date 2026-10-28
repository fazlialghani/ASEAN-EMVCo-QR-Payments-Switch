#pragma once
#include "money.h"     // Money, Currency (addAccount parameter)
#include "transaction.h"  // Transaction (post parameter, vector element)
#include <string>         // account ids
#include <unordered_map>  // id -> Account
#include <vector>         // transaction history
#include <unordered_set>   // set of already-posted transaction ids

class Ledger {
    // Ledger follows the rule of zero: it declares none of the Big 5.
    // Its members (an unordered_map of accounts and a vector of transactions)
    // are standard containers that already copy, move, and free their own
    // memory correctly. Ledger owns no raw pointer, so the compiler-generated
    // destructor, copy, and move operations do the right thing.
    public:
        void addAccount(const std::string &id, Currency currency, bool canGoNegative);
        void post(const Transaction &tr);
        Money balance(const std::string &id) const;
        bool checkInvariant() const;
    private:
        struct Account {
            Money balance;
            bool canGoNegative;
        };
        std::unordered_map<std::string, Account> accounts_;
        std::vector<Transaction> history_;
        std::unordered_set<std::string> postedIds_;
};