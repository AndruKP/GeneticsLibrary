//
// Created by andru_kfgnofp on 12/22/2024.
//

#include "Protein.h"

Protein::Protein() = default;

Protein::Protein(std::vector<Aminoacid> chain): chain(std::move(chain)) {
}
