#pragma once
#include "money.h"     // Money (type of the amount_ field)
#include <string>         // id_, from_, to_
#include <utility>        // std::move in the member initializer list

class Transaction {
    //Creates an immutable record of one transfer
    //(id, sender, receiver, amount); getters provide read-only access.
    public:
        Transaction(std::string id, std::string from, std::string to, Money amount) :
        id_{std::move(id)},
        from_{std::move(from)},
        to_{std::move(to)},
        amount_{std::move(amount)} {} //MIL

        const std::string &id() const {return id_;}
        const std::string &from() const {return from_;}
        const std::string &to() const {return to_;}
        const Money &amount() const {return amount_;}
    private:
        std::string id_, from_, to_;
        Money amount_;
};