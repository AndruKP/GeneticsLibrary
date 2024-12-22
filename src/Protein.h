#pragma once


#include <vector>

#include "Aminoacid.h"

class Protein {
    std::vector<Aminoacid> chain{};

public:
    Protein();

    explicit Protein(std::vector<Aminoacid> chain);
};


