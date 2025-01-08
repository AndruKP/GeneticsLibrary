//
// Created by andru_kfgnofp on 1/5/2025.
//

#include "Record.h"

Record::Record(Record &&other) noexcept: seqID(std::move(other.seqID)),
                                         description(std::move(other.description)),
                                         dna(std::move(other.dna)) {
}

Record &Record::operator=(const Record &other) {
    if (this == &other)
        return *this;
    seqID = other.seqID;
    description = other.description;
    dna = other.dna;
    return *this;
}

Record &Record::operator=(Record &&other) noexcept {
    if (this == &other)
        return *this;
    seqID = std::move(other.seqID);
    description = std::move(other.description);
    dna = std::move(other.dna);
    return *this;
}

std::istream &operator>>(std::istream &is, Record &record) {
    std::string seqID_;
    std::string description_;
    std::string dnaSeq;
    std::string FASTALine;

    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    char greater;

    if (!(iss >> greater)) {
        throw std::ios_base::failure(RECORD_FIRST_CHAR_READING_ERROR_MESSAGE);
    }
    if (greater != '>') {
        throw std::ios_base::failure(RECORD_INVALID_FIRST_CHAR_ERROR_MESSAGE);
    }
    if (!(iss >> seqID_)) {
        throw std::ios_base::failure(SEQ_ID_FAILURE);
    }
    if (!(iss >> description_)) {
        throw std::ios_base::failure(DESCRIPTION_FAILURE);
    }

    if (!(is >> FASTALine)) {
        throw std::ios_base::failure(SEQUENCE_FAILURE);
    }

    while (is) {
        dnaSeq += FASTALine;
        is >> FASTALine;
    }


    record = Record(seqID_,
                    description_,
                    DNA(dnaSeq, Directionality::DIR_5_to_3));
    return is;
}

std::ostream &operator<<(std::ostream &os, const Record &record) {
    os << '>' << record.getSeqID() << ' ' << record.getDescription() << '\n';
    const std::string dna = record.getDNA().getSequence();

    // todo in case of switching to C++23 change to:
    // auto chunks = dna | std::views::chunk(FASTA_OUTPUT_LINE_SIZE);
    // for_each(chunks, [](){...});

    // todo consider changing to foreach
    for (size_t i = 0; i < dna.size(); i += FASTA_OUTPUT_LINE_SIZE) {
        os << dna.substr(i, FASTA_OUTPUT_LINE_SIZE) << '\n';
    }

    return os;
}
