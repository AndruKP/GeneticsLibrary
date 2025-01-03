#pragma once

#include <utility>

#include "constants.h"
#include "dna.h"
#include "Protein.h"
#include "sequence.h"
#include "SequenceWrapper.h"

class DNA;

class RNA : SequenceWrapper<RNA_VALIDATOR > {
public:
    explicit RNA(const std::string &seq, Directionality dir = Directionality::DIR_3_to_5);

    DNA reverseTranscribe();

    Protein translate();
};
