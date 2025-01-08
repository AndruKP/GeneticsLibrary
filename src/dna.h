#pragma once

#include <algorithm>
#include <stdexcept>

#include "constants.h"
#include "rna.h"
#include "sequence.h"
#include "SequenceWrapper.h"

class RNA;

class DNA : public SequenceWrapper<DNA_VALIDATOR > {
    ReplicationStatus replicationStatus{DEFAULT_REPL_STATUS};

    TranscriptionStatus transcriptionStatus{DEFAULT_TRNSCPT_STATUS};

public:
    DNA();

    explicit DNA(const std::string &seq,
                 Directionality dir = DEFAULT_DIRECT_STATUS,
                 ReplicationStatus repl = DEFAULT_REPL_STATUS,
                 TranscriptionStatus trnscpt = DEFAULT_TRNSCPT_STATUS);

    explicit DNA(const Sequence &seq,
                 Directionality dir = DEFAULT_DIRECT_STATUS,
                 ReplicationStatus repl = DEFAULT_REPL_STATUS,
                 TranscriptionStatus trnscpt = DEFAULT_TRNSCPT_STATUS);

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

    void reverse() override;

    void reverseReplicationStatus();

    void reverseTranscriptionStatus();

    [[nodiscard]] RNA transcribe() const;
};
