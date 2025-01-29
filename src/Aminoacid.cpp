#include "Aminoacid.h"

Aminoacid::Aminoacid(const std::string &codon) {
    if (!TRANSLATION_TABLE.contains(codon)) {
        throw std::invalid_argument(WRONG_CODON_ERROR_MESSAGE);
    }
    name = TRANSLATION_TABLE.at(codon);
}

std::ostream &operator<<(std::ostream &os, const Aminoacid &a) {
    return os << a.getName();
}

