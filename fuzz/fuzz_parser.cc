#include "crc.h"        // hasValidCrc
#include "tlv.h"        // TlvField, parse, findTag
#include "switch.h"     // parseAmount
#include <cstddef>      // std::size_t
#include <cstdint>      // std::uint8_t
#include <stdexcept>    // std::invalid_argument
#include <string>       // std::string
#include <vector>       // std::vector<TlvField>

extern "C" //the function name will remain the same (unchanged)

int LLVMFuzzerTestOneInput(const std::uint8_t *data, std::size_t size) {
    std::string input(reinterpret_cast<const char *>(data), size);

    hasValidCrc(input);

    std::vector<TlvField> fields;

    if (parse(input, fields)) {
        TlvField amt;
        if (findTag(fields, "54", amt)) {
            try {
                parseAmount(amt.value);
            } catch (const std::invalid_argument &) {
                 // Malformed amounts are expected; only crashes count as bugs.
            }
        }
    }
    return 0;
}
