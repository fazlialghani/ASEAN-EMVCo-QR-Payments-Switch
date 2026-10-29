#pragma once
#include "ledger.h"     // Ledger& parameter of processPayment
#include <cstdint>      // std::int64_t returned by parseAmount
#include <string>       // std::string parameters

std::int64_t parseAmount(const std::string &s);

void processPayment(Ledger &led,
                    const std::string &txId,
                    const std::string &payload,
                    const std::string &payer,
                    const std::string &merchant);