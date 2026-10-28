#pragma once
#include "currency.h"
#include <memory>
#include <string>

class PaymentScheme {
    public:
        virtual ~PaymentScheme() = default;
        virtual std::string name() const = 0;
        virtual Currency currency() const = 0;
        virtual std::string countryCode() const = 0;
};

class PromptPayScheme: public PaymentScheme {
    public:
        std::string name() const override { return "PromptPay"; }
        Currency currency() const override { return Currency::THB; }
        std::string countryCode() const override { return "TH"; }
};

class QrisScheme: public PaymentScheme {
    public:
        std::string name() const override { return "Qris"; }
        Currency currency() const override { return Currency::IDR; }
        std::string countryCode() const override { return "ID"; }
};

class PayNowScheme: public PaymentScheme {
    public:
        std::string name() const override { return "PayNow"; }
        Currency currency() const override { return Currency::SGD; }
        std::string countryCode() const override { return "SG"; }
    
};

std::unique_ptr<PaymentScheme> makeScheme(const std::string &country);