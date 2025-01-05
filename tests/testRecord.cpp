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



TEST(TestRecord, TestTrueConstructors) {
    std::string s1 = "ACGT";
    std::string s2 = "AAAA";
    std::string s3 = "GTGT";

    DNA dna1{s1, Directionality::DIR_5_to_3};
    DNA dna2{s2, Directionality::DIR_3_to_5};
    DNA dna3{"gtgt"};

    ASSERT_EQ(s1, dna1.getSequence());
    ASSERT_EQ(s2, dna2.getSequence());
    ASSERT_EQ(s3, dna3.getSequence());

    ASSERT_EQ(Directionality::DIR_5_to_3, dna1.getDirectionality());
    ASSERT_EQ(Directionality::DIR_3_to_5, dna2.getDirectionality());
    ASSERT_EQ(ReplicationStatus::LEADING, dna1.getReplicationStatus());
    ASSERT_EQ(TranscriptionStatus::TEMPLATE, dna2.getTranscriptionStatus());
}

TEST(TestRecord, TestFileExtractor) {
    std::string fileName = "croppedContig/seq_0.fna";//data/croppedContig/seq_1.fna
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