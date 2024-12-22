//
// Created by andru_kfgnofp on 12/22/2024.
//

#include "rna.h"

RNA::RNA(Sequence sequence, const Directionality directionality):
    sequence(std::move(sequence)),
    directionality(directionality) {
}


