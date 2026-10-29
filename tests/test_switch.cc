#include "switch.h"       // parseAmount, processPayment
#include "ledger.h"       // Ledger
#include "transaction.h"  // Transaction for funding the tourist
#include "money.h"        // Money
#include "currency.h"     // Currency::THB
#include <cassert>        // assert
#include <stdexcept>      // catching std::invalid_argument
#include <string>         // payload strings

