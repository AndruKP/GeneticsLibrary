#pragma once
#include <string>
#include "constants.h"
#include <stdexcept>


class Aminoacid {
    std::string name;

public:
    explicit Aminoacid(const std::string &codon);

    ~Aminoacid() = default;

    [[nodiscard]] std::string getName() const { return name; }
};

