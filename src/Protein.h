//
// Created by andru_kfgnofp on 12/22/2024.
//
#pragma once


#include <vector>

#include "Aminoacid.h"

class Protein {
    std::vector<Aminoacid> chain{};

public:
    Protein();

    explicit Protein(std::vector<Aminoacid> chain);
};


