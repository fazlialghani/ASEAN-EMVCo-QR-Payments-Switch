#include "switch.h"       // required: keeps definitions in sync with declarations
#include "crc.h"          // hasValidCrc
#include "tlv.h"          // TlvField, parse, findTag
#include "scheme.h"       // makeScheme, PaymentScheme
#include "ledger.h"       // Ledger::post
#include "transaction.h"  // Transaction
#include "money.h"        // Money
#include <cstddef>        // std::size_t for the dot position and loops
#include <cstdint>        // std::int64_t
#include <memory>         // std::unique_ptr from makeScheme
#include <stdexcept>      // std::invalid_argument
#include <string>         // std::string, find, substr
#include <vector>         // std::vector<TlvField> filled by parse

std::int64_t parseAmount(const std::string &s)
{
    //Converts a decimal amount string like "150.00" into minor units (15000)
    //without floating point, and throws on a malformed amount.

    std::size_t dot = s.find('.');
    std::string whole = s.substr(0, dot);
    std::string frac = (dot == std::string::npos) ? "" : s.substr(dot + 1);

    if (whole.empty() || frac.size() > 2)
        throw std::invalid_argument("parseAmount: invalid amount '" + s + "'");
    
    while (frac.size() < 2)
        frac.push_back('0');

    std::int64_t result = 0;
    for (std::size_t i = 0; i < whole.size(); i++) {
        char c = whole[i];
        if (c < '0' || c > '9')
            throw std::invalid_argument("parseAmount: invalid amount '" + s + "'");
        result = result * 10 + (c - '0');
    }

    for (std::size_t i = 0; i <  frac.size(); i++) {
        char c = frac[i];
        if (c < '0' || c > '9')
            throw std::invalid_argument("parseAmount: invalid amount '" + s + "'");
        result = result * 10 + (c - '0');
    }
    
    return result;
}

void processPayment(Ledger &led,
                    const std::string &txId,
                    const std::string &payload,
                    const std::string &payer,
                    const std::string &merchant)
{
    //Processes one QR payment end to end: validates the CRC, parses the TLV fields,
    //picks the scheme from tag 58, reads the amount from tag 54, and posts it to the ledger.

    //1. CRC
    if (!hasValidCrc(payload))
        throw std::invalid_argument("processPayment: bad CRC");
    
    //2. TLV
    std::vector<TlvField> fields; 
    if(!parse(payload, fields))
        throw std::invalid_argument("processPayment: bad TLV");
    
    //3. tag 58 -> scheme
    TlvField country;
    if (!findTag(fields, "58", country))
        throw std::invalid_argument("processPayment: no tag 58");
    auto scheme = makeScheme(country.value);

    //4. tag 54 -> amount
    TlvField amt;
    if (!findTag(fields, "54", amt))
        throw std::invalid_argument("processPayment: no tag 54");
    std::int64_t amount = parseAmount(amt.value);

    //5. post
    led.post(Transaction{txId, payer, merchant, Money{ scheme->currency(), amount } });
}