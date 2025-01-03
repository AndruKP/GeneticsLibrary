#include "Protein.h"

Protein::Protein() = default;

Protein::Protein(std::vector<Aminoacid> chain): chain(std::move(chain)) {
}

Aminoacid Protein::operator[](const int index) {
    try {
        return chain.at(index);
    } catch (std::out_of_range &) {
        throw std::out_of_range(PROTEIN_RANGE_EXCEPTION_MESSAGE);
    }
}

void Protein::addAminoacid(const Aminoacid &aminoacid) {
    chain.push_back(aminoacid);
}

void Protein::addAminoacid(const std::string &codon) {
    const auto aminoacid = Aminoacid(codon);
    addAminoacid(aminoacid);
}
