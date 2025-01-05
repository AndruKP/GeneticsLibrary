#pragma once
#include <algorithm>
#include <stdexcept>

#include "constants.h"
#include "sequence.h"
#include "Validators.h"

// todo second refactor: constructor: SequenceWrapper(..., Validator validator or bool/void (*func) (std::string s));
template<typename Validator=TrivialValidator>
class SequenceWrapper {
protected:
    Sequence sequence;
    Directionality directionality;

public:
    static std::string validateString(const std::string &seq) {
        std::string temp;
        std::ranges::transform(seq, std::back_inserter(temp), toupper);
        Validator::validate(temp);
        return temp;
    }

    static Sequence validateSequence(const Sequence &seq) {
        Validator::validate(seq.getSequence());
        return seq;
    }

    SequenceWrapper(const std::string &seq, Directionality dir);

    SequenceWrapper(const Sequence &seq, Directionality dir);

    SequenceWrapper(const SequenceWrapper &other);

    SequenceWrapper(SequenceWrapper &&other) noexcept;

    SequenceWrapper &operator=(const SequenceWrapper &other);

    SequenceWrapper &operator=(SequenceWrapper &&other) noexcept;

    virtual ~SequenceWrapper();

    [[nodiscard]] Directionality getDirectionality() const { return directionality; }
    [[nodiscard]] std::string getSequence() const { return sequence.getSequence(); }
    [[nodiscard]] size_t size() const { return sequence.size(); }

    void setDirectionality(const Directionality dir) { directionality = dir; }


    /// not actually "reversing string", only changes to opposite directionality member
    void reverseDirectionality();

    virtual void reverse();

    [[nodiscard]] size_t levenshteinDistance(const SequenceWrapper<Validator> &other) const;
};

template<typename Validator>
SequenceWrapper<Validator>::~SequenceWrapper() = default;


template<typename Validator>
SequenceWrapper<Validator>::SequenceWrapper(const std::string &seq,
                                            const Directionality dir): sequence(std::move(validateString(seq))),
                                                                       directionality(dir) {
}

template<typename Validator>
SequenceWrapper<Validator>::SequenceWrapper(const Sequence &seq,
                                            const Directionality dir): sequence(validateSequence(seq)),
                                                                       directionality(dir) {
}

template<typename Validator>
SequenceWrapper<Validator>::SequenceWrapper(const SequenceWrapper &other) = default;

template<typename Validator>
SequenceWrapper<
    Validator>::SequenceWrapper(SequenceWrapper<Validator> &&other) noexcept: sequence(std::move(other.sequence)),
                                                                              directionality(other.directionality) {
}

template<typename Validator>
SequenceWrapper<Validator> &SequenceWrapper<Validator>::operator=(const SequenceWrapper<Validator> &other) {
    if (this == &other) {
        return *this;
    }

    directionality = other.directionality;
    sequence = other.sequence;

    return *this;
}

template<typename Validator>
SequenceWrapper<Validator> &SequenceWrapper<Validator>::operator=(SequenceWrapper<Validator> &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    directionality = other.directionality;
    sequence = std::move(other.sequence);


    return *this;
}

template<typename Validator>
void SequenceWrapper<Validator>::reverseDirectionality() {
    if (directionality == Directionality::DIR_5_to_3) {
        directionality = Directionality::DIR_3_to_5;
    } else {
        directionality = Directionality::DIR_5_to_3;
    }
}

template<typename Validator>
void SequenceWrapper<Validator>::reverse() {
    sequence.reverse();
    reverseDirectionality();
}

template<typename Validator>
size_t SequenceWrapper<Validator>::levenshteinDistance(const SequenceWrapper<Validator> &other) const {
    return sequence.levenshteinDistance(other.sequence);
}
