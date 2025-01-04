#include "rna.h"

RNA::RNA(const std::string &seq, const Directionality dir): SequenceWrapper<RNA_VALIDATOR >(seq, dir) {
}

RNA::RNA(const Sequence &seq, const Directionality dir): SequenceWrapper<RNA_VALIDATOR >(seq, dir) {
}

DNA RNA::reverseTranscribe(const TranscriptionStatus strand) const {
    const auto &transcriptionTable =
            strand == TranscriptionStatus::CODING
                ? REVERSE_TRANSCRIPTION_TO_CODING_STRAND
                : REVERSE_TRANSCRIPTION_TO_TEMPLATE_STRAND;

    const auto RNA_Directionality =
            strand == TranscriptionStatus::CODING
                ? directionality
                : (directionality == Directionality::DIR_3_to_5
                       ? Directionality::DIR_5_to_3
                       : Directionality::DIR_3_to_5);

    const Sequence temp = sequence.translate(transcriptionTable);
    return DNA(temp, RNA_Directionality, ReplicationStatus::LEADING, strand);
}


Protein RNA::translate() const {
    Protein protein;

    if (directionality == Directionality::DIR_3_to_5) {
        const auto shift = getSequence().size() % CODON_LENGTH;
        for (auto i = getSequence().size() / CODON_LENGTH; i > 0; --i) {
            auto substr = getSequence().substr((i - 1) * CODON_LENGTH + shift, CODON_LENGTH);
            std::ranges::reverse(substr);
            protein.addAminoacid(substr);
        }
    } else {
        for (auto i = 0; i < getSequence().size() / CODON_LENGTH; ++i) {
            auto substr = getSequence().substr(i * CODON_LENGTH, CODON_LENGTH);
            protein.addAminoacid(substr);
        }
    }
    return protein;
}

