//
// Created by andru_kfgnofp on 12/22/2024.
//

#include "Aminoacid.h"

Aminoacid::Aminoacid(const std::string &codon) {
    if (!TRANSLATION_TABLE.contains(codon)) {
        throw std::invalid_argument("Codon does not exist");
    }
    name = TRANSLATION_TABLE.at(codon);
}

