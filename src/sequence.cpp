#include <utility>
#include "sequence.h"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

Sequence::Sequence(std::string sequence): sequence(std::move(sequence)) {
}

Sequence::Sequence(): Sequence("") {
}

[[maybe_unused]] void Sequence::setSequence(std::string newSeq) { sequence = std::move(newSeq); }

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
    std::ranges::replace_if(sequence, [&](const char c) {
        return charsMap.contains(c)
               && ((repl = charsMap.at(c)));
    }, repl);
}

Sequence Sequence::translate(const std::map<char, char> &charsMap) const {
    std::string temp;
    std::ranges::transform(sequence,
                           std::back_inserter(temp),
                           [&charsMap](const char c) {
                               return charsMap.contains(c) ? charsMap.at(c) : c;
                           });
    return Sequence(temp);
}

size_t Sequence::levenshteinDistance(const Sequence &other) const {
    const auto seq1 = getSequence();
    const auto seq2 = other.getSequence();

    const auto size1 = seq1.size();
    const auto size2 = seq2.size();

    if (seq1.empty()) {
        return seq2.size();
    }
    if (seq2.empty()) {
        return seq1.size();
    }

    std::vector<size_t> prevRow(size2 + 1);
    std::vector<size_t> currRow(size2 + 1);

    std::iota(prevRow.begin(), prevRow.end(), 0);

    for (size_t i = 0; i < size1; ++i) {
        currRow[0] = i + 1;

        for (size_t j = 0; j < size2; ++j) {
            auto deletionCost = prevRow[j + 1] + 1;
            auto insertionCost = currRow[j] + 1;
            auto substitutionCost = prevRow[j];
            if (seq1[i] != seq2[j]) {
                ++substitutionCost;
            }
            currRow[j + 1] = std::min({deletionCost, insertionCost, substitutionCost});
        }
        prevRow = std::move(currRow);
        currRow.reserve(size2 + 1);
    }

    return prevRow[size2];
}

size_t Sequence::damerauLevenshteinDistance(const Sequence &other) const {
    return getSequence().size() + other.getSequence().size();
}

size_t Sequence::LSCDistance(const Sequence &other) const {
    return getSequence().size() + other.getSequence().size();
}

size_t Sequence::jaroWinklerDistance(const Sequence &other) const {
    return getSequence().size() + other.getSequence().size();
}




