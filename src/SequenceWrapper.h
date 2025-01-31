#pragma once
#include <algorithm>
#include <stdexcept>

#include "constants.h"
#include "sequence.h"
#include "Validators.h"

// todo second refactor: constructor: SequenceWrapper(..., Validator validator or bool/void (*func) (std::string s));
/**
 * Wraps class Sequence to do architectural part of the job
 * Takes
 * @tparam Validator
 */
template<HasValidate Validator=TrivialValidator>
class SequenceWrapper {
protected:
    Sequence sequence;
    Directionality directionality;

    static std::string validateString(const std::string &seq) {
        std::string temp;
        std::ranges::transform(seq, std::back_inserter(temp), toupper);
        Validator::validate(temp);
        return temp;
    }

    static Sequence validateSequence(const Sequence &seq) {
        return Sequence(std::move(validateString(seq.getSequence())));
    }

public:
    /**
     *
     * @param seq
     * @param dir
     */
    explicit SequenceWrapper(const std::string &seq, Directionality dir = DEFAULT_DIRECT_STATUS);

    /**
     *
     * @param seq
     * @param dir
     */
    explicit SequenceWrapper(const Sequence &seq, Directionality dir = DEFAULT_DIRECT_STATUS);

    /**
     *
     * @param other
     */
    SequenceWrapper(const SequenceWrapper &other);

    /**
     *
     * @param other
     */
    SequenceWrapper(SequenceWrapper &&other) noexcept;

    /**
     *
     * @param other
     * @return
     */
    SequenceWrapper &operator=(const SequenceWrapper &other);

    /**
     *
     * @param other
     * @return
     */
    SequenceWrapper &operator=(SequenceWrapper &&other) noexcept;

    virtual ~SequenceWrapper();

    [[nodiscard]] Directionality getDirectionality() const { return directionality; }
    [[nodiscard]] std::string getSequence() const { return sequence.getSequence(); }
    [[nodiscard]] size_t size() const { return sequence.size(); }

    /**
     *
     * @param dir
     */
    void setDirectionality(const Directionality dir) { directionality = dir; }

    /// Reverses directionality,
    /// but not actually "reversing string", only changes to opposite the directionality member
    void reverseDirectionality();

    /**
     *
     */
    virtual void reverse();

    [[nodiscard]] size_t levenshteinDistance(const SequenceWrapper<Validator> &other) const;

    /**
    * @note Enforces directionality of other to equal directionality of this.
    * @param other SequenceWrapper instance
    * @return pair of aligned strings
    **/
    [[nodiscard]] std::pair<std::string, std::string> align(const SequenceWrapper<Validator> &other) const;

    /**
     * @note Enforces directionality of other to differ from directionality of this.
     * @param other SequenceWrapper instance
     * @return pair of aligned strings
     */
    [[nodiscard]] std::pair<std::string, std::string> alignReversedDir(const SequenceWrapper<Validator> &other) const;

    // todo in future: return signal, which result is the best (smth like pair<pair<string,string>, Signal>)
    /**
     * @note takes best (by Lev.Dist) result
     * @param other
     * @return
     */
    [[nodiscard]] std::pair<std::string, std::string> bestAlignment(const SequenceWrapper<Validator> &other) const;
};

template<HasValidate Validator>
SequenceWrapper<Validator>::~SequenceWrapper() = default;


template<HasValidate Validator>
SequenceWrapper<Validator>::SequenceWrapper(const std::string &seq,
                                            const Directionality dir): sequence(std::move(validateString(seq))),
                                                                       directionality(dir) {
}

template<HasValidate Validator>
SequenceWrapper<Validator>::SequenceWrapper(const Sequence &seq,
                                            const Directionality dir): sequence(validateSequence(seq)),
                                                                       directionality(dir) {
}

template<HasValidate Validator>
SequenceWrapper<Validator>::SequenceWrapper(const SequenceWrapper &other) = default;

template<HasValidate Validator>
SequenceWrapper<
    Validator>::SequenceWrapper(SequenceWrapper<Validator> &&other) noexcept: sequence(std::move(other.sequence)),
                                                                              directionality(other.directionality) {
}

template<HasValidate Validator>
SequenceWrapper<Validator> &SequenceWrapper<Validator>::operator=(const SequenceWrapper<Validator> &other) {
    if (this == &other) {
        return *this;
    }

    directionality = other.directionality;
    sequence = other.sequence;

    return *this;
}

template<HasValidate Validator>
SequenceWrapper<Validator> &SequenceWrapper<Validator>::operator=(SequenceWrapper<Validator> &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    directionality = other.directionality;
    sequence = std::move(other.sequence);


    return *this;
}

template<HasValidate Validator>
void SequenceWrapper<Validator>::reverseDirectionality() {
    if (directionality == Directionality::DIR_5_to_3) {
        directionality = Directionality::DIR_3_to_5;
    } else {
        directionality = Directionality::DIR_5_to_3;
    }
}

template<HasValidate Validator>
void SequenceWrapper<Validator>::reverse() {
    sequence.reverse();
    reverseDirectionality();
}

template<HasValidate Validator>
size_t SequenceWrapper<Validator>::levenshteinDistance(const SequenceWrapper<Validator> &other) const {
    return sequence.levenshteinDistance(other.sequence);
}

template<HasValidate Validator>
std::pair<std::string, std::string> SequenceWrapper<Validator>::align(const SequenceWrapper<Validator> &other) const {
    if (directionality != other.getDirectionality()) {
        return sequence.alignReversed(other.sequence);
    }
    return sequence.align(other.sequence);
}

template<HasValidate Validator>
std::pair<std::string, std::string> SequenceWrapper<Validator>::alignReversedDir(
    const SequenceWrapper<Validator> &other) const {
    if (directionality == other.getDirectionality()) {
        return sequence.alignReversed(other.sequence);
    }
    return sequence.align(other.sequence);
}

template<HasValidate Validator>
std::pair<std::string, std::string> SequenceWrapper<Validator>::bestAlignment(
    const SequenceWrapper<Validator> &other) const {
    auto bestAlignmentResult = align(other);
    size_t min = Sequence(bestAlignmentResult.first).levenshteinDistance(Sequence(bestAlignmentResult.second));

    auto tempAlignmentResult = alignReversedDir(other);
    auto tempDist = Sequence(tempAlignmentResult.first).levenshteinDistance(Sequence(tempAlignmentResult.second));
    if (tempDist < min) {
        bestAlignmentResult = tempAlignmentResult;
    }
    return bestAlignmentResult;
}
