#pragma once


#include <vector>

#include "Aminoacid.h"

class Protein {
    std::vector<Aminoacid> chain{};

public:
    Protein();

    explicit Protein(std::vector<Aminoacid> chain);

    Aminoacid operator[](int index);

    void addAminoacid(const Aminoacid &aminoacid);

    void addAminoacid(const std::string &codon);

    [[nodiscard]] std::string toString() const;
};


