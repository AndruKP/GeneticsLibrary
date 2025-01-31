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
    /**
     *
     */
    DNA();

    /**
     *
     * @param seq
     * @param dir
     * @param repl
     * @param trnscpt
     */
    explicit DNA(const std::string &seq,
                 Directionality dir = DEFAULT_DIRECT_STATUS,
                 ReplicationStatus repl = DEFAULT_REPL_STATUS,
                 TranscriptionStatus trnscpt = DEFAULT_TRNSCPT_STATUS);

    /**
     *
     * @param seq
     * @param dir
     * @param repl
     * @param trnscpt
     */
    explicit DNA(const Sequence &seq,
                 Directionality dir = DEFAULT_DIRECT_STATUS,
                 ReplicationStatus repl = DEFAULT_REPL_STATUS,
                 TranscriptionStatus trnscpt = DEFAULT_TRNSCPT_STATUS);

    /**
     *
     * @param other
     */
    DNA(const DNA &other);

    /**
     *
     * @param other
     */
    DNA(DNA &&other) noexcept;

    /**
     *
     * @param other
     * @return
     */
    DNA &operator=(const DNA &other);

    /**
     *
     * @param other
     * @return
     */
    DNA &operator=(DNA &&other) noexcept;

    ~DNA() override;

    /**
     * 
     * @return replicationStatus
     */
    [[nodiscard]] ReplicationStatus getReplicationStatus() const { return replicationStatus; }

    [[nodiscard]] TranscriptionStatus getTranscriptionStatus() const { return transcriptionStatus; }

    void setReplicationStatus(const ReplicationStatus repl) { replicationStatus = repl; }

    void setTranscriptionStatus(const TranscriptionStatus trans) { transcriptionStatus = trans; }

    /**
     * 
     */
    void complement();

    /**
     * 
     */
    void reverse() override;

    /**
     * 
     */
    void reverseComplement();

    /**
     * 
     */
    void reverseReplicationStatus();

    /**
     * 
     */
    void reverseTranscriptionStatus();

    /**
     * 
     * @param other
     * @return
     */
    [[nodiscard]] std::pair<std::string, std::string> alignComplement(const DNA &other) const;

    /**
     * 
     * @param other 
     * @return 
     */
    [[nodiscard]] std::pair<std::string, std::string> alignComplementReversedDir(const DNA &other) const;

    /**
     * 
     * @param other 
     * @return 
     */
    [[nodiscard]] std::pair<std::string, std::string> bestAlignment(const DNA &other) const;

    /**
     * 
     * @return 
     */
    [[nodiscard]] RNA transcribe() const;
};
