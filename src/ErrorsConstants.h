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

const std::string RECORD_FIRST_CHAR_READING_ERROR_MESSAGE("Failed to parse first character");
const std::string RECORD_INVALID_FIRST_CHAR_ERROR_MESSAGE("Invalid starting character");
const std::string SEQ_ID_FAILURE("Failed to parse seqID");
const std::string DESCRIPTION_FAILURE("Failed to parse description");
const std::string SEQUENCE_FAILURE("Failed to parse sequence");

const std::string GET_RECORD_ERROR_MESSAGE = "Record index is out of range: idx = ";
const std::string END_OF_ERROR_MESSAGE_APPEND_SIZE = "while size = ";

const std::string FASTAReader_WARNING = "DNA Validator have failed, probably because of non-standard base in sequence: ";