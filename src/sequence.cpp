#include <utility>
#include "sequence.h"

#include <algorithm>
#include <ranges>
#include <vector>

std::pair<std::string, std::string> Sequence::baseCaseSolver(const std::string &seq1,
                                                             const std::string &seq2,
                                                             const long long insertionCost,
                                                             const long long deletionCost,
                                                             const long long matchCost,
                                                             const long long mismatchCost,
                                                             const size_t size2) const {
    std::string alignedSeq1, alignedSeq2;

    std::vector<long long> prevRow(size2 + 1);

    long long _i = 0;
    std::ranges::generate(prevRow.begin(), prevRow.end(), [&]() {
        long long temp = _i;
        _i += insertionCost;
        return temp;
    });

    auto currRow = alignScoreRow(seq1, seq2, insertionCost, deletionCost, matchCost,
                                 mismatchCost);

    bool found = false;
    auto j = size2;

    while (!found || j > 0) {
        if (!found && j > 0 && currRow[j] == prevRow[j - 1] + (seq1[0] == seq2[j - 1] ? matchCost : mismatchCost)) {
            alignedSeq1.insert(0, 1, seq1[0]);
            alignedSeq2.insert(0, 1, seq2[j - 1]);
            found = true;
            j--;
            // todo: check if deletionCost isn't needed instead of insertion
        } else if (!found && currRow[j] == prevRow[j] + insertionCost) {
            alignedSeq1.insert(0, 1, seq1[0]);
            alignedSeq2.insert(0, 1, '-');
            found = true;
        } else {
            alignedSeq1.insert(0, 1, '-');
            alignedSeq2.insert(0, 1, seq2[j - 1]);
            j--;
        }
    }
    return std::make_pair(alignedSeq1, alignedSeq2);
}

std::pair<std::string, std::string> Sequence::_align(const std::string &seq1, const std::string &seq2,
                                                     const long long insertionCost,
                                                     const long long deletionCost,
                                                     const long long matchCost,
                                                     const long long mismatchCost) const {
    std::string alignedSeq1;
    std::string alignedSeq2;

    const auto size1 = seq1.size(); // m
    const auto size2 = seq2.size(); // n

    if (seq1.empty()) {
        alignedSeq1 = std::string(size2, '-');
        alignedSeq2 = seq2;
        return std::make_pair(alignedSeq1, alignedSeq2);
    }
    if (seq2.empty()) {
        alignedSeq2 = std::string(size1, '-');
        alignedSeq1 = seq1;
        return std::make_pair(alignedSeq1, alignedSeq2);
    }
    // emulate Needleman–Wunsch algorithm, where size1 = 1
    if (size1 == 1 || size2 == 1) {
        if (size1 != 1) {
            auto [fst, snd] = baseCaseSolver(seq2, seq1, insertionCost, deletionCost, matchCost, mismatchCost, size1);
            return make_pair(snd, fst);
        }
        return baseCaseSolver(seq1, seq2, insertionCost, deletionCost, matchCost, mismatchCost, size2);
    }


    const auto mid = size1 / 2;

    std::string revSeq1, revSeq2;
    std::ranges::reverse_copy(seq1, std::back_inserter(revSeq1));
    std::ranges::reverse_copy(seq2, std::back_inserter(revSeq2));

    const auto scoreLeft = alignScoreRow(seq1.substr(0, mid), seq2, insertionCost, deletionCost, matchCost,
                                         mismatchCost);
    const auto scoreRight = alignScoreRow(revSeq1.substr(0, size1 - mid), revSeq2, insertionCost, deletionCost,
                                          matchCost,
                                          mismatchCost);

    // todo use some algo instead (std::max_element)...
    size_t splitIndex = 0;
    auto maxScore = LONG_LONG_MIN;

    for (auto j = 0; j <= size2; ++j) {
        auto score = scoreLeft[j] + scoreRight[size2 - j];
        if (score > maxScore) {
            maxScore = score;
            splitIndex = j;
        }
    }

    // Recursively align the two halves
    auto [seq1L, seq2L] = _align(seq1.substr(0, mid), seq2.substr(0, splitIndex),
                                 insertionCost, deletionCost, matchCost, mismatchCost);
    auto [seq1R, seq2R] = _align(seq1.substr(mid), seq2.substr(splitIndex),
                                 insertionCost, deletionCost, matchCost, mismatchCost);

    alignedSeq1 = seq1L + seq1R;
    alignedSeq2 = seq2L + seq2R;

    return std::make_pair(alignedSeq1, alignedSeq2);
}

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
        return size2;
    }
    if (seq2.empty()) {
        return size1;
    }
    //
    // std::vector<size_t> prevRow(size2 + 1);
    // std::vector<size_t> currRow(size2 + 1);
    //
    // std::iota(prevRow.begin(), prevRow.end(), 0);
    //
    // for (size_t i = 0; i < size1; ++i) {
    //     currRow[0] = i + 1;
    //
    //     for (size_t j = 0; j < size2; ++j) {
    //         auto deletionCost = prevRow[j + 1] + 1;
    //         auto insertionCost = currRow[j] + 1;
    //         auto substitutionCost = prevRow[j];
    //         if (seq1[i] != seq2[j]) {
    //             ++substitutionCost;
    //         }
    //         currRow[j + 1] = std::min({deletionCost, insertionCost, substitutionCost});
    //     }
    //     prevRow = std::move(currRow);
    //     currRow.reserve(size2 + 1);
    // }
    //
    // return prevRow[size2];
    return WagnerFisher<size_t>(seq1, seq2, 1, 1, 0, 1, true)[size2];
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

std::pair<std::string, std::string> Sequence::align(const Sequence &other,
                                                    const long long insertionCost,
                                                    const long long deletionCost,
                                                    const long long matchCost,
                                                    const long long mismatchCost) const {
    return _align(getSequence(), other.getSequence(), insertionCost, deletionCost, matchCost, mismatchCost);
}

std::pair<std::string, std::string> Sequence::alignReversed(const Sequence &other,
                                                            const long long insertionCost,
                                                            const long long deletionCost,
                                                            const long long matchCost,
                                                            const long long mismatchCost) const {
    std::string temp = other.getSequence();
    std::ranges::reverse(temp);
    return _align(getSequence(), temp, insertionCost, deletionCost, matchCost, mismatchCost);
}

std::vector<long long> Sequence::alignScoreRow(const std::string &sequence1, const std::string &sequence2,
                                               const long long insertionCost,
                                               const long long deletionCost,
                                               const long long matchCost,
                                               const long long mismatchCost) const {
    return WagnerFisher<long long>(sequence1, sequence2, insertionCost, deletionCost, matchCost, mismatchCost, false);
}

template<typename T>
std::vector<T> Sequence::WagnerFisher(const std::string &sequence1,
                                      const std::string &sequence2,
                                      const T insertion, const T deletion, const T match, const T mismatch,
                                      const bool inverted) const {
    const auto size1 = sequence1.size();
    const auto size2 = sequence2.size();

    // if (sequence1.empty()) {
    //     return sequence2.size();
    // }
    // if (sequence2.empty()) {
    //     return sequence1.size();
    // }

    std::vector<T> prevRow(size2 + 1);
    std::vector<T> currRow(size2 + 1);

    T _i = 0;
    std::ranges::generate(prevRow.begin(), prevRow.end(), [&]() {
        T temp = _i;
        _i += insertion;
        return temp;
    });

    for (size_t i = 0; i < size1; ++i) {
        // todo doublecheck correctness
        currRow[0] = (i + 1) * deletion;

        for (size_t j = 0; j < size2; ++j) {
            auto deletionCost = prevRow[j + 1] + deletion;
            auto insertionCost = currRow[j] + insertion;
            auto substitutionCost = prevRow[j];

            if (sequence1[i] != sequence2[j]) {
                substitutionCost += mismatch;
            } else {
                substitutionCost += match;
            }
            if (inverted) {
                currRow[j + 1] = std::min({deletionCost, insertionCost, substitutionCost});
            } else {
                currRow[j + 1] = std::max({deletionCost, insertionCost, substitutionCost});
            }
        }
        // todo swap
        // prevRow = std::move(currRow);
        // currRow.reserve(size2 + 1);
        std::swap(prevRow, currRow);
    }

    return prevRow;
}
