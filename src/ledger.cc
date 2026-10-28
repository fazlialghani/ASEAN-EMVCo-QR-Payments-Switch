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
    //Moves money from one account to another after checking
    //every rule first; if any check fails, no balance changes.
    if (tr.amount().minorUnits() <= 0)
        throw std::invalid_argument("post: amount. must be positive");

    auto from = accounts_.find(tr.from());
    auto to = accounts_.find(tr.to());

    if (from == accounts_.end() || to == accounts_.end())
        throw std::invalid_argument("post: unknown account");
    
    if (from == to)
        throw std::invalid_argument("post: from and to are the same");
    
    //CHECK
    Money newFrom = from->second.balance - tr.amount();
    Money newTo = to->second.balance + tr.amount();

    if (!from->second.canGoNegative && newFrom.minorUnits() < 0)
        throw std::invalid_argument("post: '" + tr.from() + "'would go negative");
    
    //COMMIT
    history_.push_back(tr);
    from->second.balance = newFrom;
    to->second.balance = newTo;
}

Money Ledger::balance(const std::string &id) const
{
    //Returns an account’s current balance without modifying the ledger, and
    //throws if the account does not exist.
    auto acc = accounts_.find(id);

    if (acc == accounts_.end())
        throw std::invalid_argument("balance: unknown account '" + id + "'");

    return acc->second.balance;
}

bool Ledger::checkInvariant() const
{
    //verifies that the ledger is always balanced: the sum of all account balances
    //in each currency must be zero. Money in the ledger can only move between
    //accounts; it can never be created or destroyed.

    //If any total is non-zero, post has a bug. The randomized test calls it after
    //every transfer, so any bug is caught at the exact transfer that caused it.
    std::unordered_map<Currency, std::int64_t> total;

    for (const auto &entry : accounts_) {
        const Money &m = entry.second.balance;
        total[m.currency()] += m.minorUnits();
    }

    for (const auto &entry : total) {
        if (entry.second != 0)
            return false;
    }
    return true;
}