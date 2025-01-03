#include "rna.h"

RNA::RNA(const std::string &seq, const Directionality dir): SequenceWrapper<RNA_VALIDATOR>(seq, dir) {
}

DNA RNA::reverseTranscribe() {
    //todo finish
    return DNA("ACGT");
}

Protein RNA::translate() {
    //todo finish
    return {};
}

