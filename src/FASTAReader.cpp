//
// Created by andru_kfgnofp on 1/6/2025.
//

#include "FASTAReader.h"

#include <iostream>

void FASTAReader::addRecord(const Record &record) {
    records.push_back(record);
}

void FASTAReader::addRecord(const std::string &seqID, const std::string &description, const std::string &sequence) {
    try {
        addRecord(Record(seqID,
                         description,
                         DNA(sequence, Directionality::DIR_5_to_3)));
    } catch (std::invalid_argument &e) {
        std::cerr << FASTAReader_WARNING
                << seqID << ' '
                << e.what() << std::endl;
    }
}

size_t FASTAReader::size() const {
    return records.size();
}

Record FASTAReader::getRecord(const size_t idx) const {
    try {
        return records[idx];
    } catch (std::out_of_range &e) {
        const auto message = GET_RECORD_ERROR_MESSAGE
                             + std::to_string(idx)
                             + END_OF_ERROR_MESSAGE_APPEND_SIZE
                             + std::to_string(size());

        throw std::out_of_range(message);
    }
}


std::istream &operator>>(std::istream &is, FASTAReader &fastaReader) {
    std::string line;

    std::string currSequence;
    std::string currSeqID;
    std::string currDescription;

    while (std::getline(is, line)) {
        if (line.empty()) {
            continue;
        }

        if (line[0] == '>') {
            if (!currSequence.empty()) {
                fastaReader.addRecord(currSeqID, currDescription, currSequence);
                currSequence.clear();
            }
            std::istringstream iss(line);
            char greater;
            iss >> greater >> currSeqID;
            iss >> currDescription;
        } else {
            currSequence += line;
        }
    }

    if (!currSequence.empty()) {
        fastaReader.addRecord(currSeqID, currDescription, currSequence);
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const FASTAReader &fastaReader) {
    for (auto &record: fastaReader.getSequence()) {
        os << record;
    }
    return os;
}
