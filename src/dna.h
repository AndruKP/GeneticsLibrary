#pragma once

#include <algorithm>
#include <stdexcept>

#include "constants.h"
#include "rna.h"
#include "sequence.h"
#include "SequenceWrapper.h"

class RNA;

class DNA : public SequenceWrapper {
    ReplicationStatus replicationStatus{ReplicationStatus::LEADING};

    TranscriptionStatus transcriptionStatus{TranscriptionStatus::TEMPLATE};

public:
    std::string getAllowedSymbols() override { return CORRECT_DNA_BASES; }


    explicit DNA(const std::string &seq,
                 Directionality dir = Directionality::DIR_3_to_5,
                 ReplicationStatus repl = ReplicationStatus::LEADING,
                 TranscriptionStatus trnscpt = TranscriptionStatus::TEMPLATE);

    DNA(const DNA &other);

    DNA(DNA &&other) noexcept;

    DNA &operator=(const DNA &other);

    DNA &operator=(DNA &&other) noexcept;

    ~DNA() override;

    [[nodiscard]] ReplicationStatus getReplicationStatus() const { return replicationStatus; }

    [[nodiscard]] TranscriptionStatus getTranscriptionStatus() const { return transcriptionStatus; }

    void setReplicationStatus(const ReplicationStatus repl) { replicationStatus = repl; }

    void setTranscriptionStatus(const TranscriptionStatus trans) { transcriptionStatus = trans; }

    void complement();

    void reverseComplement();

    [[nodiscard]] RNA transcribe(const RNA &other) const;
};
