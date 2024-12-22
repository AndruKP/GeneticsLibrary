//
// Created by andru_kfgnofp on 12/14/2024.
//

#pragma once

#include <algorithm>
#include <stdexcept>

#include "constants.h"
#include "rna.h"
#include "sequence.h"
#include "SequenceWrapper.h"

class RNA;

class DNA : public SequenceWrapper {
    //Directionality directionality{Directionality::DIR_3_to_5};

    ReplicationStatus replicationStatus{ReplicationStatus::LEADING};

    TranscriptionStatus transcriptionStatus{TranscriptionStatus::TEMPLATE};

    //Sequence sequence;

public:
    std::string getAllowedSymbols() override { return CORRECT_DNA_BASES; }

    //static bool checkSequenceCorrectness(const std::string &seq);

    //static bool checkSymbolCorrectness(char c);


    explicit DNA(const std::string &seq,
                 Directionality dir = Directionality::DIR_3_to_5,
                 ReplicationStatus repl = ReplicationStatus::LEADING,
                 TranscriptionStatus trnscpt = TranscriptionStatus::TEMPLATE);

    DNA(const DNA &other);

    DNA(DNA &&other) noexcept;

    DNA &operator=(const DNA &other);

    DNA &operator=(DNA &&other) noexcept;

    ~DNA() override;

    //[[nodiscard]] Directionality getDirectionality() const { return directionality; }

    [[nodiscard]] ReplicationStatus getReplicationStatus() const { return replicationStatus; }

    [[nodiscard]] TranscriptionStatus getTranscriptionStatus() const { return transcriptionStatus; }

    //[[nodiscard]] std::string getSequence() const { return sequence.getSequence(); }

    //void setDirectionality(const Directionality dir) { directionality = dir; }

    void setReplicationStatus(const ReplicationStatus repl) { replicationStatus = repl; }

    void setTranscriptionStatus(const TranscriptionStatus trans) { transcriptionStatus = trans; }

    //void reverseDirectionality();

    //void reverse();

    void complement();

    void reverseComplement();

    [[nodiscard]] RNA transcribe(const RNA &other) const;
};
