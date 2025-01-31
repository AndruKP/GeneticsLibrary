//
// Created by andru_kfgnofp on 1/5/2025.
//
#pragma once
#include <utility>

#include "dna.h"

/**
 *
 */
class Record {
    std::string seqID;
    std::string description;
    DNA dna;

public:
    /**
     * 
     */
    Record() = default;

    /**
     * 
     * @param seqID 
     * @param description 
     * @param dna 
     */
    Record(std::string seqID, std::string description, DNA dna): seqID(std::move(seqID)),
                                                                 description(std::move(description)),
                                                                 dna(std::move(dna)) {
    }

    /**
     *
     * @param other
     */
    Record(const Record &other) = default;

    /**
     *
     * @param other
     */
    Record(Record &&other) noexcept;

    /**
     *
     * @param other
     * @return
     */
    Record &operator=(const Record &other);

    /**
     *
     * @param other
     * @return
     */
    Record &operator=(Record &&other) noexcept;

    /**
     *
     * @return
     */
    [[nodiscard]] size_t size() const { return dna.size(); }

    /**
     *
     * @return
     */
    [[nodiscard]] DNA getDNA() const { return dna; }

    /**
     *
     * @return
     */
    [[nodiscard]] std::string getSeqID() const { return seqID; }

    /**
     *
     * @return
     */
    [[nodiscard]] std::string getDescription() const { return description; }
};

/**
 *
 * @param is
 * @param record
 * @return
 */
std::istream &operator>>(std::istream &is, Record &record);

/**
 *
 * @param os
 * @param record
 * @return
 */
std::ostream &operator<<(std::ostream &os, const Record &record);
