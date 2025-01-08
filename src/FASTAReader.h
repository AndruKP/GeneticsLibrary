//
// Created by andru_kfgnofp on 1/6/2025.
//
#pragma once
#include <vector>

#include "record.h"


class FASTAReader {
    std::vector<Record> records;

public:
    FASTAReader() = default;

    explicit FASTAReader(const std::vector<Record> &records): records(records) {
    }

    void addRecord(const Record &record);

    void addRecord(const std::string &seqID, const std::string &description, const std::string &sequence);

    [[nodiscard]] size_t size() const;

    [[nodiscard]] Record getRecord(size_t idx) const;

    [[nodiscard]] const std::vector<Record> &getSequence() const { return records; };
};

std::istream &operator>>(std::istream &is, FASTAReader &fastaReader);

std::ostream &operator<<(std::ostream &os, const FASTAReader &fastaReader);
