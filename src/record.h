//
// Created by andru_kfgnofp on 1/5/2025.
//
#pragma once
#include <utility>

#include "dna.h"

class Record {
    std::string seqID;
    std::string description;
    DNA dna;

public:
    Record() = default;

    Record(std::string seqID, std::string description, DNA dna): seqID(std::move(seqID)),
                                                                 description(std::move(description)),
                                                                 dna(std::move(dna)) {
    }

    Record(const Record &other) = default;

    Record(Record &&other) noexcept;

    Record &operator=(const Record &other);

    Record &operator=(Record &&other) noexcept;

    [[nodiscard]] size_t size() const { return dna.size(); }

    [[nodiscard]] DNA getDNA() const { return dna; }

    [[nodiscard]] std::string getSeqID() const { return seqID; }

    [[nodiscard]] std::string getDescription() const { return description; }
};

std::istream &operator>>(std::istream &is, Record &record);

std::ostream &operator<<(std::ostream &os, const Record &record);
