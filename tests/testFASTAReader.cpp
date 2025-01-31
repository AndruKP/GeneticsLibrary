// Copyright 2005, Google Inc.
// All rights reserved.

//
// Created by andru_kfgnofp on 12/14/2024.
//

#include <fstream>
#include <iostream>

#include "FASTAReader.h"
#include "gtest/gtest.h"

using namespace ::testing;

TEST(TestFASTAReader, TestConstructorsAndIndices) {
    std::vector<Record> records;
    records.push_back(Record("0", "descr", DNA("ACGT")));
    records.push_back(Record("1", "descr", DNA("ACGT")));

    FASTAReader reader(records);
    ASSERT_EQ(reader.size(), 2);
    ASSERT_EQ(reader.getRecord(0).getSeqID(), "0");

    ASSERT_EQ(reader.getRecord(1).getSeqID(), "1");
}

TEST(TestFASTAReader, TestIndexError) {
    std::vector<Record> records;
    records.push_back(Record("0", "descr", DNA("ACGT")));
    records.push_back(Record("1", "descr", DNA("ACGT")));

    FASTAReader reader(records);
    ASSERT_EQ(reader.size(), 2);
    ASSERT_EQ(reader.getRecord(0).getSeqID(), "0");

    try {
        auto x = reader.getRecord(2);
    } catch (FASTAReaderIndexException &e) {
        ASSERT_EQ(std::string(e.what()), "Record index is out of range: idx = 2 while size = 2");
    }
}

TEST(TestFASTAReader, TestAddRecord) {
    FASTAReader reader;
    reader.addRecord(Record("0", "descr", DNA("ACGT")));
    ASSERT_EQ(reader.size(), 1);
    ASSERT_EQ(reader.getRecord(0).getSeqID(), "0");

    reader.addRecord("1", "1", "ACGT");
    ASSERT_EQ(reader.size(), 2);
    ASSERT_EQ(reader.getRecord(1).getSeqID(), "1");
    ASSERT_EQ(reader.getRecord(1).getDNA().getSequence(), "ACGT");
}

TEST(TestFASTAReader, TestFileExtractor) {
    std::string fileName = "GCA_000006425.2_ASM642v2_genomic.fna";
    std::ifstream file(fileName);

    ASSERT_TRUE(file.is_open());
    FASTAReader reader;

    file >> reader;
    int hello = 3;
    file.close();
    // TODO end with some meaningful ASSERT

    ASSERT_NE(reader.size(), 0);
}

TEST(TestFASTAReader, TestFileInsertion) {
    std::string inputFileName1 = "GCA_000006425.2_ASM642v2_genomic.fna";
    std::ifstream input1(inputFileName1);

    ASSERT_TRUE(input1.is_open());
    FASTAReader reader1;

    input1 >> reader1;
    input1.close();


    std::string outputFilename = "GCA_000006425.2_ASM642v2_genomic.fna";
    std::ofstream output(outputFilename);

    ASSERT_TRUE(output.is_open());

    output << reader1;
    output.close();

    std::ifstream input2(outputFilename);
    ASSERT_TRUE(input2.is_open());
    FASTAReader reader2;
    input2 >> reader2;
    input2.close();

    ASSERT_EQ(reader1.size(), reader2.size());
    ASSERT_EQ(reader1.getRecord(3).getSeqID(), reader2.getRecord(3).getSeqID());
}

// TEST(TestFASTAReader, TestComparisonAndFileExtractor) {
//     std::string fileName0 = "croppedContig/seq_0.fna";
//     std::string fileName1 = "croppedContig/seq_2.fna";
//
//     std::ifstream file0(fileName0);
//     std::ifstream file1(fileName1);
//
//     Record record0;
//     Record record1;
//
//     file0 >> record0;
//     file1 >> record1;
//
//
//     DNA dna0 = record0.getDNA();
//     DNA dna1 = record1.getDNA();
//
//     ASSERT_NE(dna1.getSequence(), dna0.getSequence());
// }
