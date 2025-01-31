#pragma once
#include <map>
#include <string>
#include <vector>
#include "constants.h"

class Sequence {
    std::string sequence;

    [[nodiscard]] std::pair<std::string, std::string> baseCaseSolver(const std::string &seq1, const std::string &seq2,
                                                                     long long insertionCost, long long deletionCost,
                                                                     long long matchCost,
                                                                     long long mismatchCost,
                                                                     size_t size2) const;

    [[nodiscard]] std::pair<std::string, std::string> _align(const std::string &seq1, const std::string &seq2,
                                                             const long long insertionCost,
                                                             const long long deletionCost,
                                                             const long long matchCost,
                                                             const long long mismatchCost) const;

    /**
     *
     * @tparam T type of number - to avoid ambiguous conversions
     * @param sequence1 first string to align
     * @param sequence2 second string to align
     * @param insertion cost of insertions
     * @param deletion cost of deletions
     * @param match cost of match
     * @param mismatch cost of mismatch
     * @param inverted if false, counts max of all possible scores; otherwise counts min
     * @return Levenshtein distance or "cost" of alignment
     */
    template<typename T>
    std::vector<T> WagnerFisher(const std::string &sequence1,
                                const std::string &sequence2,
                                const T insertion, const T deletion, const T match, const T mismatch,
                                bool inverted = false) const;

    [[nodiscard]] std::vector<long long> alignScoreRow(const std::string &sequence1,
                                                       const std::string &sequence2,
                                                       const long long insertionCost = INSERTION_COST,
                                                       const long long deletionCost = DELETION_COST,
                                                       const long long matchCost = MATCH_COST,
                                                       const long long mismatchCost = MISMATCH_COST) const;

public:
    /**
     *
     * @param sequence
     */
    explicit Sequence(std::string sequence);

    /**
     *
     */
    Sequence();

    [[nodiscard]] std::string getSequence() const { return sequence; }

    [[nodiscard]] size_t size() const { return sequence.size(); }

    /**
     *
     * @param other
     */
    Sequence(const Sequence &other);

    /**
     *
     * @param other
     */
    Sequence(Sequence &&other) noexcept;

    /**
     *
     * @param other
     * @return
     */
    Sequence &operator=(const Sequence &other);

    /**
     *
     * @param other
     * @return
     */
    Sequence &operator=(Sequence &&other) noexcept;

    ~Sequence();

    /**
     *
     */
    void reverse();

    /**
     *
     * @param charsMap
     */
    void replaceChars(const std::map<char, char> &charsMap);

    /**
     *
     * @param charsMap
     * @return
     */
    [[nodiscard]] Sequence translate(const std::map<char, char> &charsMap) const;

    /**
     * @brief Modification of Wagner–Fischer algorithm for computation the edit distance (Levenshtein's distance)
     * @param other the sequence used for comparison with `this`
     * @return
     */
    [[nodiscard]] size_t levenshteinDistance(const Sequence &other) const;


    /**
     *
     * @param other
     * @param insertionCost
     * @param deletionCost
     * @param matchCost
     * @param mismatchCost
     * @return
     */
    [[nodiscard]] std::pair<std::string, std::string> align(const Sequence &other,
                                                            const long long insertionCost = INSERTION_COST,
                                                            const long long deletionCost = DELETION_COST,
                                                            const long long matchCost = MATCH_COST,
                                                            const long long mismatchCost = MISMATCH_COST) const;

    /**
     *
     * @param other
     * @param insertionCost
     * @param deletionCost
     * @param matchCost
     * @param mismatchCost
     * @return
     */
    [[nodiscard]] std::pair<std::string, std::string> alignReversed(const Sequence &other,
                                                                    const long long insertionCost = INSERTION_COST,
                                                                    const long long deletionCost = DELETION_COST,
                                                                    const long long matchCost = MATCH_COST,
                                                                    const long long mismatchCost = MISMATCH_COST) const;
};


