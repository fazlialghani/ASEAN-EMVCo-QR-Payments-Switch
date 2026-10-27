#include "ledger.h"       // required: keeps definitions in sync with declarations
#include "money.h"        // Money, arithmetic, minorUnits()
#include "currency.h"     // Currency
#include <cstdint>        // std::int64_t (checkInvariant, block 4)
#include <stdexcept>      // std::invalid_argument
#include <string>         // building error messages
#include <unordered_map>  // per-currency totals (block 4)

void Ledger::addAccount(const std::string &id, Currency currency, bool canGoNegative)
{
    //Opens a new account with a zero balance in the given currency, and throws
    //if the id already exists.
    bool idDNE = accounts_.emplace(id, Account{Money{currency, 0}, canGoNegative}).second;
    if (!idDNE)
        throw std::invalid_argument("addAccount: duplicate id");
}

void Ledger::post(const Transaction &tr)
{
    
}

