//
// Created by andru_kfgnofp on 1/3/2025.
//
#pragma once
#include <sstream>
#include <stdexcept>
#include <bits/ranges_algo.h>
#include <concepts>


#include "constants.h"

/// Class T needs to have static method T::validate(const::std string &seq) to be Validator
/// @note because T::validate() is void, T::validate() should throw exceptions by itself
template<typename T>
concept HasValidate = requires(const std::string &seq)
{
    { T::validate(seq) } -> std::same_as<void>;
};


template<const std::string &allowedSymbols>
class SimpleValidator {
    static bool checkSymbolCorrectness(const char c);

    static bool checkSequenceCorrectness(const std::string &seq);

    static std::string getErrorMessage();

public:
    /**
     *
     * @param seq
     */
    static void validate(const std::string &seq);
};

template<const std::string &allowedSymbols>
bool SimpleValidator<allowedSymbols>::checkSymbolCorrectness(const char c) {
    return std::ranges::any_of(allowedSymbols,
                               [c](const char currChar) { return currChar == c; });
}

template<const std::string &allowedSymbols>
bool SimpleValidator<allowedSymbols>::checkSequenceCorrectness(const std::string &seq) {
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
    /**
     *
     * @param seq
     */
    static void validate(const std::string &seq) {
    }
};
