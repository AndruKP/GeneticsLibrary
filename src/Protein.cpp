#include "Protein.h"

Protein::Protein() = default;

Protein::Protein(std::vector<Aminoacid> chain): chain(std::move(chain)) {
}
