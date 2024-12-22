//
// Created by andru_kfgnofp on 12/14/2024.
//

#include "dna.h"

bool DNA::checkSequenceCorrectness(const std::string &seq) {
    if (seq.empty()) {
        return false;
    }
    return std::ranges::all_of(seq, checkSymbolCorrectness);
}

bool DNA::checkSymbolCorrectness(const char c) {
    return std::any_of(CORRECT_DNA_BASES,
                       CORRECT_DNA_BASES + NUM_OF_CORRECT_DNA_BASES,
                       [c](const char currChar) { return currChar == c; });
}

DNA::DNA(const std::string &seq,
         const Directionality dir,
         const ReplicationStatus repl,
         const TranscriptionStatus trnscpt) {
    if (!checkSequenceCorrectness(seq)) {
        throw std::invalid_argument(DNA_WRONG_SYMBOL_MESSAGE);
    }

    directionality = dir;
    replicationStatus = repl;
    transcriptionStatus = trnscpt;

    sequence.setSequence(seq);
}

DNA::DNA(const DNA &other) = default;

DNA::DNA(DNA &&other) noexcept: directionality(other.directionality),
                                replicationStatus(other.replicationStatus),
                                transcriptionStatus(other.transcriptionStatus),
                                sequence(std::move(other.sequence)) {
}

DNA &DNA::operator=(const DNA &other) {
    if (this == &other) {
        return *this;
    }

    directionality = other.directionality;
    replicationStatus = other.replicationStatus;
    transcriptionStatus = other.transcriptionStatus;
    sequence = other.sequence;

    return *this;
}

DNA &DNA::operator=(DNA &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    directionality = other.directionality;
    replicationStatus = other.replicationStatus;
    transcriptionStatus = other.transcriptionStatus;
    sequence = std::move(other.sequence);

    return *this;
}

DNA::~DNA() = default;

void DNA::reverseDirectionality() {
    if (directionality == Directionality::DIR_5_to_3) {
        directionality = Directionality::DIR_3_to_5;
    }
    else {
        directionality = Directionality::DIR_5_to_3;
    }
}

void DNA::reverse() {
    sequence.reverse();
    reverseDirectionality();
}

/// by doing complement to 3'-5' strand -- we should get 5'-3' strand (literally the complement)
/// to get the same directionality, use reverseComplement();
void DNA::complement() {
    sequence.replaceChars(DNA_COMPLEMENTS);
    reverseDirectionality();
}

void DNA::reverseComplement() {
    reverse();
    complement();
}


