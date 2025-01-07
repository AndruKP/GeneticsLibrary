// Copyright 2005, Google Inc.
// All rights reserved.

//
// Created by andru_kfgnofp on 12/14/2024.
//

#include <fstream>
#include <iostream>
#include "gtest/gtest.h"
#include "record.h"

using namespace ::testing;

TEST(TestRecord, TestFileExtractor) {
    std::string fileName = "croppedContig/seq_0.fna"; //data/croppedContig/seq_1.fna
    std::ifstream file(fileName);

    Record record;

    // std::string debugLine;
    // file >> debugLine;
    // file >> debugLine;
    // file >> debugLine;
    // file >> debugLine;

    file >> record;
    auto size = record.size();
    file.close();
    // TODO end with some meaningful ASSERT
}

TEST(TestRecord, TestComparisonAndFileExtractor) {
    std::string fileName0 = "croppedContig/seq_0.fna";
    std::string fileName1 = "croppedContig/seq_2.fna";

    std::ifstream file0(fileName0);
    std::ifstream file1(fileName1);

    Record record0;
    Record record1;

    file0 >> record0;
    file1 >> record1;


    DNA dna0 = record0.getDNA();
    DNA dna1 = record1.getDNA();

    ASSERT_NE(dna1.getSequence(), dna0.getSequence());
}
