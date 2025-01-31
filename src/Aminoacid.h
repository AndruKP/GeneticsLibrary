#pragma once
#include <string>
#include "constants.h"
#include <stdexcept>


/**
 * Class for representing one aminoacid
 * @note Amino-acid's codes are defined in \file constants.h
 */
class Aminoacid {
    std::string name;

public:
    /**
     * Creates Aminoacid from codon (3 bases)
     * @param codon string of length 3 representing part of mRNA
     */
    explicit Aminoacid(const std::string &codon);

    ~Aminoacid() = default;

    /**
     * @return 3-letter code of aminoacid defined in TRANSLATION_TABLE
     */
    [[nodiscard]] std::string getName() const { return name; }
};

/**
 * Writes name of Aminoacid to output stream
 * @param os output stream
 * @param a Aminoacid
 * @return output stream
 */
std::ostream &operator<<(std::ostream &os, const Aminoacid &a);

