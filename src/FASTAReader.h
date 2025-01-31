//
// Created by andru_kfgnofp on 1/6/2025.
//
#pragma once
#include <vector>

#include "Record.h"


class FASTAReader {
    std::vector<Record> records;

public:
    /**
     *
     */
    FASTAReader() = default;

    /**
     *
     * @param records
     */
    explicit FASTAReader(const std::vector<Record> &records): records(records) {
    }

    /**
     *
     * @param record
     */
    void addRecord(const Record &record);

    /**
     *
     * @param seqID
     * @param description
     * @param sequence
     */
    void addRecord(const std::string &seqID, const std::string &description, const std::string &sequence);

    [[nodiscard]] size_t size() const;

    [[nodiscard]] Record getRecord(size_t idx) const;

    [[nodiscard]] const std::vector<Record> &getSequence() const { return records; };
};

/**
 *
 * @param is
 * @param fastaReader
 * @return
 */
std::istream &operator>>(std::istream &is, FASTAReader &fastaReader);

/**
 *
 * @param os
 * @param fastaReader
 * @return
 */
std::ostream &operator<<(std::ostream &os, const FASTAReader &fastaReader);
