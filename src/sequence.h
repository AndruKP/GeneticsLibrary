//
// Created by andru_kfgnofp on 12/14/2024.
//

#pragma once
#include <map>
#include <string>


class Sequence {
    std::string sequence;

public:
    explicit Sequence(std::string sequence);

    Sequence();

    [[nodiscard]] std::string getSequence() const { return sequence; }

    void setSequence(std::string newSeq);

    Sequence(const Sequence &other);

    Sequence(Sequence &&other) noexcept;

    Sequence &operator=(const Sequence &other);

    Sequence &operator=(Sequence &&other) noexcept;

    ~Sequence();

    void reverse();

    void replaceChars(const std::map<char, char> &charsMap);
};
