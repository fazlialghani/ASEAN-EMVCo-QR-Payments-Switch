#pragma once
#include <string>

enum class Currency { IDR, THB, SGD };

std::string toCurrency(Currency c);