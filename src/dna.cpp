#include "dna.h"

DNA::DNA(): DNA("",
                Directionality::DIR_3_to_5,
                ReplicationStatus::LEADING,
                TranscriptionStatus::CODING) {
}

DNA::DNA(const std::string &seq,
         const Directionality dir,
         const ReplicationStatus repl,
         const TranscriptionStatus trnscpt): SequenceWrapper<DNA_VALIDATOR >(seq, dir),
                                             replicationStatus(repl),
                                             transcriptionStatus(trnscpt) {
}

DNA::DNA(const Sequence &seq,
         const Directionality dir,
         const ReplicationStatus repl,
         const TranscriptionStatus trnscpt): SequenceWrapper<DNA_VALIDATOR >(seq, dir),
                                             replicationStatus(repl),
                                             transcriptionStatus(trnscpt) {
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

void DNA::reverse() {
    SequenceWrapper<SimpleValidator<CORRECT_DNA_BASES> >::reverse();
    reverseReplicationStatus();
    reverseTranscriptionStatus();
}

void DNA::reverseReplicationStatus() {
    if (replicationStatus == ReplicationStatus::LAGGING) {
        replicationStatus = ReplicationStatus::LEADING;
    } else if (replicationStatus == ReplicationStatus::LEADING) {
        replicationStatus = ReplicationStatus::LAGGING;
    }
}

void DNA::reverseTranscriptionStatus() {
    if (transcriptionStatus == TranscriptionStatus::CODING) {
        transcriptionStatus = TranscriptionStatus::TEMPLATE;
    } else if (transcriptionStatus == TranscriptionStatus::TEMPLATE) {
        transcriptionStatus = TranscriptionStatus::CODING;
    }
}

RNA DNA::transcribe() const {
    //todo Directionality change to bool

    const auto &transcriptionTable =
            transcriptionStatus == TranscriptionStatus::CODING
                ? TRANSCRIPTION_TABLE_FOR_CODING_STRAND
                : TRANSCRIPTION_TABLE_FOR_TEMPLATE_STRAND;

    const auto RNA_Directionality =
            transcriptionStatus == TranscriptionStatus::CODING
                ? directionality
                : (directionality == Directionality::DIR_3_to_5
                       ? Directionality::DIR_5_to_3
                       : Directionality::DIR_3_to_5);

    const Sequence temp = sequence.translate(transcriptionTable);
    return RNA(temp, RNA_Directionality);
}


