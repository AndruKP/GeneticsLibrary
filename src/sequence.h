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

    [[nodiscard]] Sequence translate(const std::map<char, char> &charsMap) const;

    [[nodiscard]] size_t levenshteinDistance(const Sequence &other) const;

    [[nodiscard]] size_t damerauLevenshteinDistance(const Sequence &other) const;

    [[nodiscard]] size_t LSCDistance(const Sequence &other) const;

    [[nodiscard]] size_t jaroWinklerDistance(const Sequence &other) const;
};
