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