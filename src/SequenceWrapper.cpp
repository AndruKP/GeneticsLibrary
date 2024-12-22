#include "SequenceWrapper.h"

bool SequenceWrapper::checkSequenceCorrectness(const std::string &seq) {
    if (seq.empty()) {
        return false;
    }
    for (char it: seq) {
        if (!checkSymbolCorrectness(it)) {
            return false;
        }
    }
    return true;
}

SequenceWrapper::~SequenceWrapper() = default;

bool SequenceWrapper::checkSymbolCorrectness(const char c) {
    auto allowed = getAllowedSymbols();
    return std::ranges::any_of(allowed,
                               [c](const char currChar) { return currChar == c; });
}

SequenceWrapper::SequenceWrapper(const std::string &seq,
                                 const Directionality dir) {
    if (!checkSequenceCorrectness(seq)) {
        //todo fix undoing throw to fix "needs of polymorphism during construction in rna and dna
        //throw std::invalid_argument(SEQUENCE_WRAPPER_WRONG_SYMBOL_MESSAGE);
        return;
    }

    directionality = dir;
    sequence.setSequence(seq);
}

SequenceWrapper::SequenceWrapper(const SequenceWrapper &other) = default;

SequenceWrapper::SequenceWrapper(SequenceWrapper &&other) noexcept: sequence(std::move(other.sequence)),
                                                                    directionality(other.directionality) {
}

SequenceWrapper &SequenceWrapper::operator=(const SequenceWrapper &other) {
    if (this == &other) {
        return *this;
    }

    directionality = other.directionality;
    sequence = other.sequence;

    return *this;
}

SequenceWrapper &SequenceWrapper::operator=(SequenceWrapper &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    directionality = other.directionality;
    sequence = std::move(other.sequence);


    return *this;
}

void SequenceWrapper::reverseDirectionality() {
    if (directionality == Directionality::DIR_5_to_3) {
        directionality = Directionality::DIR_3_to_5;
    } else {
        directionality = Directionality::DIR_5_to_3;
    }
}

void SequenceWrapper::reverse() {
    sequence.reverse();
    reverseDirectionality();
}
