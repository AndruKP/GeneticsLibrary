//
// Created by andru_kfgnofp on 12/14/2024.
//

#include <utility>
#include "sequence.h"

#include <algorithm>

Sequence::Sequence(std::string sequence): sequence(std::move(sequence)) {
}

Sequence::Sequence(): Sequence("") {
}

void Sequence::setSequence(std::string newSeq) { sequence = std::move(newSeq); }

Sequence::Sequence(const Sequence &other) = default;

Sequence::Sequence(Sequence &&other) noexcept: sequence(std::move(other.sequence)) {
}

Sequence &Sequence::operator=(const Sequence &other) {
    if (this == &other)
        return *this;
    sequence = other.sequence;
    return *this;
}

Sequence &Sequence::operator=(Sequence &&other) noexcept {
    if (this == &other)
        return *this;
    sequence = std::move(other.sequence);
    return *this;
}

Sequence::~Sequence() = default;

void Sequence::reverse() {
    std::ranges::reverse(sequence);
}

void Sequence::replaceChars(const std::map<char, char> &charsMap) {
    char repl;
    std::ranges::replace_if(sequence, [&](char c) {
        return charsMap.contains(c)
               && ((repl = charsMap.at(c)));
    }, repl);
}



