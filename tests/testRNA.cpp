// Copyright 2005, Google Inc.
// All rights reserved.

//
// Created by andru_kfgnofp on 12/14/2024.
//

#include <iostream>
#include "gtest/gtest.h"
#include "rna.h"

using namespace ::testing;


//TEST(TestRNA, TestTrueConstructors) {
//    std::string s1 = "ACGT";
//    std::string s2 = "AAAA";
//    std::string s3 = "GTGT";
//
//    DNA dna1{s1, Directionality::DIR_5_to_3};
//    DNA dna2{s2, Directionality::DIR_3_to_5};
//    DNA dna3{s3};
//
//    ASSERT_EQ(s1, dna1.getSequence());
//    ASSERT_EQ(s2, dna2.getSequence());
//    ASSERT_EQ(s3, dna3.getSequence());
//
//    ASSERT_EQ(Directionality::DIR_5_to_3, dna1.getDirectionality());
//    ASSERT_EQ(Directionality::DIR_3_to_5, dna2.getDirectionality());
//    ASSERT_EQ(ReplicationStatus::LEADING, dna1.getReplicationStatus());
//    ASSERT_EQ(TranscriptionStatus::TEMPLATE, dna2.getTranscriptionStatus());
//}
//
//TEST(TestRNA, TestFalseConstructors) {
//    std::string exceptionMessage1;
//    std::string exceptionMessage2;
//
//    const std::string s1 = "ACxT";
//    const std::string s2 = "";
//
//    try {
//        DNA dna1{s1};
//    } catch (std::invalid_argument &ex) {
//        exceptionMessage1 = ex.what();
//    }
//    ASSERT_EQ(exceptionMessage1, "SimpleValidator's check of seq is failed on string: \"ACGT\"");
//
//    try {
//        DNA dna2{s2};
//    } catch (std::invalid_argument &ex) {
//        exceptionMessage2 = ex.what();
//    }
//    ASSERT_EQ(exceptionMessage2, SIMPLE_VALIDATOR_WRONG_SEQUENCE_MESSAGE + " \"ACGT\"");
//}
//
//TEST(TestRNA, TestCopyConstructors) {
//    std::string s1 = "ACGT";
//    DNA dna1{s1, Directionality::DIR_5_to_3};
//    ASSERT_EQ(s1, dna1.getSequence());
//
//    DNA dna3{dna1};
//    ASSERT_EQ(s1, dna3.getSequence());
//}
//
//TEST(TestRNA, TestCopyOperators) {
//    std::string s1 = "ACGT";
//    std::string s2 = "AAAA";
//
//    DNA dna1{s1, Directionality::DIR_5_to_3};
//    DNA dna2{s2, Directionality::DIR_3_to_5};
//
//    ASSERT_EQ(s1, dna1.getSequence());
//    ASSERT_EQ(s2, dna2.getSequence());
//
//    dna1 = dna2;
//    ASSERT_EQ(s2, dna1.getSequence());
//    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());
//    dna2 = dna2;
//    ASSERT_EQ(s2, dna2.getSequence());
//}
//
//TEST(TestRNA, TestMoveConstructors) {
//    std::string s1 = "ACGT";
//
//    DNA dna1{s1, Directionality::DIR_5_to_3};
//    ASSERT_EQ(s1, dna1.getSequence());
//
//    DNA dna3{std::move(dna1)};
//    ASSERT_EQ(s1, dna3.getSequence());
//    ASSERT_EQ(Directionality::DIR_5_to_3, dna3.getDirectionality());
//
//    ASSERT_TRUE(dna1.getSequence().empty());
//}
//
//TEST(TestRNA, TestMoveOperators) {
//    std::string s1 = "ACGT";
//    std::string s2 = "AAAA";
//
//    DNA dna1{s1};
//    DNA dna2{s2};
//
//    ASSERT_EQ(s1, dna1.getSequence());
//    ASSERT_EQ(s2, dna2.getSequence());
//
//    dna1 = std::move(dna2);
//    ASSERT_EQ(s2, dna1.getSequence());
//    dna1 = std::move(dna1);
//    ASSERT_EQ(s2, dna1.getSequence());
//}
//
//TEST(TestRNA, TestReverseDNA) {
//    std::string s1 = "ACGT";
//    DNA dna1{s1, Directionality::DIR_5_to_3};
//    ASSERT_EQ(s1, dna1.getSequence());
//    ASSERT_EQ(Directionality::DIR_5_to_3, dna1.getDirectionality());
//
//    dna1.reverse();
//
//    ASSERT_EQ("TGCA", dna1.getSequence());
//    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());
//}
//
//TEST(TestRNA, TestComplement) {
//    std::string s1 = "CGTATGCTA";
//    std::string s2 = "GCATACGAT";
//    DNA dna1{s1, Directionality::DIR_3_to_5};
//
//    ASSERT_EQ(s1, dna1.getSequence());
//
//    dna1.complement();
//    ASSERT_EQ(s2, dna1.getSequence());
//    ASSERT_EQ(Directionality::DIR_5_to_3, dna1.getDirectionality());
//
//    dna1.complement();
//    ASSERT_EQ(s1, dna1.getSequence());
//    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());
//}
//
//TEST(TestRNA, TestReverseComplement) {
//    std::string s1 = "CGTATGCTA";
//    std::string s2 = "TAGCATACG";
//    DNA dna1{s1, Directionality::DIR_3_to_5};
//
//    ASSERT_EQ(s1, dna1.getSequence());
//
//    dna1.reverseComplement();
//    ASSERT_EQ(s2, dna1.getSequence());
//    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());
//
//    dna1.reverseComplement();
//    ASSERT_EQ(s1, dna1.getSequence());
//    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());
//}
//
//TEST(TestRNA, IdempotenceOfComplements) {
//    //complement + reverse complement + reverse = 2x complement + 2x reverse = doing nothing
//
//    std::string s1 = "CGTATGCTA";
//
//    DNA dna1{s1, Directionality::DIR_3_to_5};
//    ASSERT_EQ(s1, dna1.getSequence());
//    dna1.complement();
//    dna1.reverseComplement();
//    dna1.reverse();
//
//    ASSERT_EQ(s1, dna1.getSequence());
//    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());
//}
//
TEST(TestRNA, TestTranscription) {
    const std::string s1 = "ACACACUUUGGG";
    const std::string s2 = "UGUGUGAAACCC";
    const RNA rna1(s1, Directionality::DIR_3_to_5);
    const RNA rna2{s2, Directionality::DIR_5_to_3};

    auto dna1 = rna1.reverseTranscribe(TranscriptionStatus::CODING);
    auto dna2 = rna2.reverseTranscribe(TranscriptionStatus::TEMPLATE);

    ASSERT_EQ(dna1.getSequence(), "ACACACTTTGGG");
    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());

    ASSERT_EQ(dna2.getSequence(), "ACACACTTTGGG");
    ASSERT_EQ(Directionality::DIR_3_to_5, dna2.getDirectionality());
}
