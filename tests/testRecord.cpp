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
    ASSERT_TRUE(file.is_open());
    Record record;

    file >> record;
    file.close();
    // TODO end with some meaningful ASSERT
}

TEST(TestRecord, TestComparisonAndFileExtractor) {
    std::string fileName0 = "croppedContig/seq_0.fna";
    std::string fileName1 = "croppedContig/seq_2.fna";

    std::ifstream file0(fileName0);
    ASSERT_TRUE(file0.is_open());
    std::ifstream file1(fileName1);
    ASSERT_TRUE(file1.is_open());

    Record record0;
    Record record1;

    file0 >> record0;
    file1 >> record1;


    DNA dna0 = record0.getDNA();
    DNA dna1 = record1.getDNA();

    ASSERT_NE(dna1.getSequence(), dna0.getSequence());
}

TEST(TestRecord, TestInsertion) {
    std::string inputFile1 = "croppedContig/seq_0.fna";
    std::ifstream input1(inputFile1);
    ASSERT_TRUE(input1.is_open());
    Record record1;
    input1 >> record1;
    input1.close();

    std::string outputFile = "croppedContig/seq_0_written.fna";
    std::ofstream output(outputFile);
    ASSERT_TRUE(output.is_open());
    output << record1;
    output.close();


    std::string inputFile2 = "croppedContig/seq_0_written.fna";
    std::ifstream input2(inputFile2);
    ASSERT_TRUE(input2.is_open());
    Record record2;
    input2 >> record2;

    ASSERT_EQ(record1.getDNA().getSequence(), record2.getDNA().getSequence());
    ASSERT_EQ(record1.getSeqID(), record2.getSeqID());
    ASSERT_EQ(record1.getDescription(), record2.getDescription());
}