//
// Created by andru_kfgnofp on 1/3/2025.
//
#pragma once
#include <sstream>
#include <stdexcept>
#include <bits/ranges_algo.h>

#include "constants.h"

template<const std::string &allowedSymbols>
class SimpleValidator {
    static bool checkSymbolCorrectness(const char c);

    static bool checkSequenceCorrectness(const std::string &seq);

    static std::string getErrorMessage();

public:
    static void validate(const std::string &seq);
};

template<const std::string &allowedSymbols>
bool SimpleValidator<allowedSymbols>::checkSymbolCorrectness(const char c) {
    return std::ranges::any_of(allowedSymbols,
                               [c](const char currChar) { return currChar == c; });
}

template<const std::string &allowedSymbols>
bool SimpleValidator<allowedSymbols>::checkSequenceCorrectness(const std::string &seq) {
    // if (seq.empty()) {
    //     return false;
    // }
    return std::ranges::all_of(seq, checkSymbolCorrectness);
}

template<const std::string &allowedSymbols>
std::string SimpleValidator<allowedSymbols>::getErrorMessage() {
    std::ostringstream oss;
    oss << SIMPLE_VALIDATOR_WRONG_SEQUENCE_MESSAGE << " \"" << allowedSymbols << '"';
    return oss.str();
}

template<const std::string &allowedSymbols>
void SimpleValidator<allowedSymbols>::validate(const std::string &seq) {
    if (!checkSequenceCorrectness(seq)) {
        const auto message = getErrorMessage();
        throw std::invalid_argument(message);
    }
}

#define DNA_VALIDATOR SimpleValidator<CORRECT_DNA_BASES>
#define RNA_VALIDATOR SimpleValidator<CORRECT_RNA_BASES>

class TrivialValidator {
public:
    static void validate(const std::string &seq) {
    }
};
