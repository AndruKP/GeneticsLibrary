// Copyright 2005, Google Inc.
// All rights reserved.

//
// Created by andru_kfgnofp on 12/14/2024.
//

#include <fstream>
#include <iostream>
#include "gtest/gtest.h"
#include "Record.h"

using namespace ::testing;

TEST(TestRecord, TestConstructors) {
    auto x = DNA("ACGT");

    Record r1;
    Record r2("1", "descr", x);

    ASSERT_EQ(r1.getDescription(), "");
    ASSERT_EQ(r2.getDescription(), "descr");

    ASSERT_EQ(r1.getSeqID(), "");
    ASSERT_EQ(r2.getSeqID(), "1");

    ASSERT_EQ(r2.getDNA().getSequence(), x.getSequence());
}


TEST(TestRecord, TestCopyConstructor) {
    DNA dna("AGCT");
    Record original("1", "description", dna);

    Record copyConstructed(original);

    ASSERT_EQ(copyConstructed.getSeqID(), original.getSeqID());
    ASSERT_EQ(copyConstructed.getDescription(), original.getDescription());
    ASSERT_EQ(copyConstructed.getDNA().getSequence(), original.getDNA().getSequence());
}

TEST(TestRecord, TestCopyOperator) {
    DNA dna("AGCT");
    Record original("2", "description", dna);

    Record copyAssigned;
    copyAssigned = original;

    ASSERT_EQ(copyAssigned.getSeqID(), original.getSeqID());
    ASSERT_EQ(copyAssigned.getDescription(), original.getDescription());
    ASSERT_EQ(copyAssigned.getDNA().getSequence(), original.getDNA().getSequence());
}

TEST(TestRecord, TestMoveConstructor) {
    Record tempForMove("3", "description", DNA("TTAG"));
    Record moveConstructed(std::move(tempForMove));

    ASSERT_EQ(moveConstructed.getSeqID(), "3");
    ASSERT_EQ(moveConstructed.getDescription(), "description");
    ASSERT_EQ(moveConstructed.getDNA().getSequence(), "TTAG");

    ASSERT_TRUE(tempForMove.getSeqID().empty());
    ASSERT_TRUE(tempForMove.getDescription().empty());
    ASSERT_TRUE(tempForMove.getDNA().getSequence().empty());
}

TEST(TestRecord, TestMoveOperator) {
    Record temp("4", "description", DNA("GGCC"));
    Record moveAssigned;

    moveAssigned = Record("1", "1", DNA());
    moveAssigned = std::move(temp);

    ASSERT_EQ(moveAssigned.getSeqID(), "4");
    ASSERT_EQ(moveAssigned.getDescription(), "description");
    ASSERT_EQ(moveAssigned.getDNA().getSequence(), "GGCC");

    ASSERT_TRUE(temp.getSeqID().empty());
    ASSERT_TRUE(temp.getDescription().empty());
    ASSERT_TRUE(temp.getDNA().getSequence().empty());
}


TEST(TestRecord, TestFileExtractor) {
    std::string fileName = "croppedContig/seq_0.fna"; //data/croppedContig/seq_1.fna
    std::ifstream file(fileName);
    ASSERT_TRUE(file.is_open());
    Record record;

    file >> record;
    file.close();

    ASSERT_EQ(record.getSeqID(), "LQXE01000001.1");
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
