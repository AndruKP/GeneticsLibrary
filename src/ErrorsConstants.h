//
// Created by andru_kfgnofp on 1/3/2025.
//
#pragma once
#include <string>
#include <stdexcept>

const std::string DNA_WRONG_SYMBOL_MESSAGE = "DNA::checkCorrectness() failed: there is a bad symbol in sequence";
const std::string SEQUENCE_WRAPPER_WRONG_SYMBOL_MESSAGE(
    "::checkCorrectness() failed: there is a bad symbol in sequence");
const std::string SIMPLE_VALIDATOR_WRONG_SEQUENCE_MESSAGE("SimpleValidator's check of seq is failed on string:");

const std::string RECORD_FIRST_CHAR_READING_ERROR_MESSAGE("Failed to parse first character");
const std::string RECORD_INVALID_FIRST_CHAR_ERROR_MESSAGE("Invalid starting character");
const std::string SEQ_ID_FAILURE("Failed to parse seqID");
const std::string DESCRIPTION_FAILURE("Failed to parse description");
const std::string SEQUENCE_FAILURE("Failed to parse sequence");

const std::string GET_RECORD_ERROR_MESSAGE = "Record index is out of range: idx = ";
const std::string GET_PROTEIN_ERROR_MESSAGE = "Protein index is out of range: idx = ";
const std::string END_OF_ERROR_MESSAGE_APPEND_SIZE = "while size = ";

const std::string FASTAReader_WARNING =
        "DNA Validator have failed, probably because of non-standard base in sequence: ";

const std::string WRONG_CODON_ERROR_MESSAGE = "Codon does not exist";


/**
 * Out of range exception for FASTAReader
 */
class FASTAReaderIndexException : public std::out_of_range {
public:
    FASTAReaderIndexException(size_t idx, size_t size);
};

inline FASTAReaderIndexException::FASTAReaderIndexException(const size_t idx, const size_t size): std::out_of_range(
    GET_RECORD_ERROR_MESSAGE
    + std::to_string(idx)
    + " "
    + END_OF_ERROR_MESSAGE_APPEND_SIZE
    + std::to_string(size)) {
}

class ProteinIndexException : public std::out_of_range {
public:
    ProteinIndexException(size_t idx, size_t size): std::out_of_range(
        GET_PROTEIN_ERROR_MESSAGE
        + std::to_string(idx)
        + " "
        + END_OF_ERROR_MESSAGE_APPEND_SIZE
        + std::to_string(size)) {
    }
};



