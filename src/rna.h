#pragma once

#include <utility>

#include "constants.h"
#include "dna.h"
#include "Protein.h"
#include "sequence.h"
#include "SequenceWrapper.h"

class DNA;

class RNA : public SequenceWrapper<RNA_VALIDATOR > {
public:
    /**
     *
     * @param seq
     * @param dir
     */
    explicit RNA(const std::string &seq, Directionality dir = Directionality::DIR_3_to_5);

    /**
     *
     * @param seq
     * @param dir
     */
    explicit RNA (const Sequence &seq, Directionality dir = Directionality::DIR_3_to_5);

    /**
     *
     * @param strand
     * @return
     */
    [[nodiscard]] DNA reverseTranscribe(TranscriptionStatus strand = TranscriptionStatus::CODING) const;

    /**
     *
     * @return
     */
    [[nodiscard]] Protein translate() const;
};
