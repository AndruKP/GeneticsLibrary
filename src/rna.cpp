#include "rna.h"

RNA::RNA(const std::string &seq, const Directionality dir): SequenceWrapper<RNA_VALIDATOR>(seq, dir) {
    //todo fix needs of polymorphic behaviour in constructor (that one silly AllowedSymbols...)

    // if (!checkSequenceCorrectness(seq)) {
    //     throw std::invalid_argument(SEQUENCE_WRAPPER_WRONG_SYMBOL_MESSAGE);
    // }
    //
    // directionality = dir;
    // sequence.setSequence(seq);
}

DNA RNA::reverseTranscribe() {
    //todo finish
    return DNA("ACGT");
}

Protein RNA::translate() {
    //todo finish
    return {};
}

