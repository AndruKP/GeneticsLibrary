//
// Created by andru_kfgnofp on 1/3/2025.
//
#pragma once
#include <string>

const std::string DNA_WRONG_SYMBOL_MESSAGE = "DNA::checkCorrectness() failed: there is a bad symbol in sequence";
const std::string SEQUENCE_WRAPPER_WRONG_SYMBOL_MESSAGE(
    "::checkCorrectness() failed: there is a bad symbol in sequence");
const std::string PROTEIN_RANGE_EXCEPTION_MESSAGE = "Index is out of range in Protein::operator[]";
const std::string SIMPLE_VALIDATOR_WRONG_SEQUENCE_MESSAGE("SimpleValidator's check of seq is failed on string:");
