#pragma once


#include <vector>

#include "Aminoacid.h"

class Protein {
    std::vector<Aminoacid> chain{};

public:
    /**
     *
     */
    Protein();

    /**
     *
     * @param chain
     */
    explicit Protein(std::vector<Aminoacid> chain);

    /**
     *
     * @param index
     * @return
     */
    Aminoacid operator[](int index) const;

    /**
     *
     * @param aminoacid
     */
    void addAminoacid(const Aminoacid &aminoacid);

    /**
     *
     * @param codon
     */
    void addAminoacid(const std::string &codon);

    /**
     *
     * @return
     */
    [[nodiscard]] size_t size() const { return chain.size(); }

    /**
     *
     * @return
     */
    [[nodiscard]] std::string toString() const;
};


