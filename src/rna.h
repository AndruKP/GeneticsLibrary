//
// Created by andru_kfgnofp on 12/22/2024.
//
#pragma once

#include <utility>

#include "sequence.h"
#include "dna.h"
#include "constants.h"


class RNA {
public:
    explicit RNA(Sequence sequence, Directionality directionality = Directionality::DIR_3_to_5);

private:
    Sequence sequence;
    Directionality directionality{Directionality::DIR_3_to_5};

public:
    Sequence getSequence() { return sequence; }

    [[nodiscard]] Directionality getDirectionality() const { return directionality; }
};



