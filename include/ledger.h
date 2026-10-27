#pragma once
#include "money.h"     // Money, Currency (addAccount parameter)
#include "transaction.h"  // Transaction (post parameter, vector element)
#include <string>         // account ids
#include <unordered_map>  // id -> Account
#include <vector>         // transaction history

class Ledger {
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
};