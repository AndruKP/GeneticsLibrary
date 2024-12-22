#include "dna.h"

DNA::DNA(const std::string &seq,
         const Directionality dir,
         const ReplicationStatus repl,
         const TranscriptionStatus trnscpt): SequenceWrapper(seq, dir) {

    //todo fix needs of polymorphic behaviour in constructor (that one silly AllowedSymbols...)
    if (!checkSequenceCorrectness(seq)) {
        throw std::invalid_argument(SEQUENCE_WRAPPER_WRONG_SYMBOL_MESSAGE);
    }

    directionality = dir;
    sequence.setSequence(seq);
    replicationStatus = repl;
    transcriptionStatus = trnscpt;
}

DNA::DNA(const DNA &other) = default;

DNA::DNA(DNA &&other) noexcept: SequenceWrapper(std::move(other)),
                                replicationStatus(other.replicationStatus),
                                transcriptionStatus(other.transcriptionStatus) {
}

DNA &DNA::operator=(const DNA &other) = default;

DNA &DNA::operator=(DNA &&other) noexcept {
    SequenceWrapper::operator=(std::move(other));
    replicationStatus = other.replicationStatus;
    transcriptionStatus = other.transcriptionStatus;

    return *this;
}

DNA::~DNA() = default;


/// by doing complement to 3'-5' strand -- we should get 5'-3' strand (literally the complement)
/// to get the same directionality, use reverseComplement();
void DNA::complement() {
    sequence.replaceChars(DNA_COMPLEMENTS);
    reverseDirectionality();
}

void DNA::reverseComplement() {
    reverse();
    complement();
}

RNA DNA::transcribe(const RNA &other) const {
    //todo finish
    std::string DUMMY;
    RNA rna(DUMMY, Directionality::DIR_5_to_3);
    return rna;
}


