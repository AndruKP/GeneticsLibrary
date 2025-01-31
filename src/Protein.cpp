#include "Protein.h"

#include <sstream>

Protein::Protein() = default;

Protein::Protein(std::vector<Aminoacid> chain): chain(std::move(chain)) {
}

Aminoacid Protein::operator[](const int index) const {
    try {
        return chain.at(index);
    } catch (std::out_of_range &) {
        throw ProteinIndexException(index, size());
    }
}

void Protein::addAminoacid(const Aminoacid &aminoacid) {
    chain.push_back(aminoacid);
}

void Protein::addAminoacid(const std::string &codon) {
    const auto aminoacid = Aminoacid(codon);
    addAminoacid(aminoacid);
}

std::string Protein::toString() const {
    std::ostringstream oss;

    for (const Aminoacid &aminoacid: chain) {
        oss << aminoacid;
    }

    return oss.str();
}
