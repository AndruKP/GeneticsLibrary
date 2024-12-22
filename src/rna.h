//
// Created by andru_kfgnofp on 12/22/2024.
//
#pragma once

#include <utility>

#include "constants.h"
#include "dna.h"
#include "Protein.h"
#include "sequence.h"
#include "SequenceWrapper.h"

class DNA;

class RNA : SequenceWrapper {
public:
    explicit RNA(const std::string &seq, Directionality dir = Directionality::DIR_3_to_5);

    DNA reverseTranscribe();

    Protein translate();
};
