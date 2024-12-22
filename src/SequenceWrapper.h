#pragma once
#include <algorithm>
#include <stdexcept>

#include "constants.h"
#include "sequence.h"


class SequenceWrapper {
protected:
    Sequence sequence;
    Directionality directionality;

public:
    virtual std::string getAllowedSymbols() {
        return "";
    }

    SequenceWrapper(const std::string &seq, Directionality dir);

    SequenceWrapper(const SequenceWrapper &other);

    SequenceWrapper(SequenceWrapper &&other) noexcept;

    SequenceWrapper &operator=(const SequenceWrapper &other);

    SequenceWrapper &operator=(SequenceWrapper &&other) noexcept;

    virtual ~SequenceWrapper();

    bool checkSequenceCorrectness(const std::string &seq);

    bool checkSymbolCorrectness(char c);

    [[nodiscard]] Directionality getDirectionality() const { return directionality; }
    [[nodiscard]] std::string getSequence() const { return sequence.getSequence(); }

    void setDirectionality(const Directionality dir) { directionality = dir; }


    /// not actually "reversing string", only changes to opposite directionality member
    void reverseDirectionality();

    void reverse();
};




