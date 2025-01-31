// Copyright 2005, Google Inc.
// All rights reserved.

//
// Created by andru_kfgnofp on 12/14/2024.
//

#include <fstream>
#include <iostream>
#include "gtest/gtest.h"
#include "SequenceWrapper.h"

using namespace ::testing;

TEST(TestSequenceWrapper, TestConstructors) {
    const SequenceWrapper<DNA_VALIDATOR > empty("");

    ASSERT_EQ(empty.getSequence(), "");
    ASSERT_EQ(empty.getDirectionality(), DEFAULT_DIRECT_STATUS);

    const SequenceWrapper<DNA_VALIDATOR > seqW1("AAAA");
    ASSERT_EQ(seqW1.getSequence(), "AAAA");
    ASSERT_EQ(seqW1.getDirectionality(), DEFAULT_DIRECT_STATUS);

    const SequenceWrapper<DNA_VALIDATOR > seqW2(Sequence("aCTTg"), Directionality::DIR_5_to_3);
    ASSERT_EQ(seqW2.getSequence(), "ACTTG");
    ASSERT_EQ(seqW2.getDirectionality(), Directionality::DIR_5_to_3);

    try {
        SequenceWrapper<DNA_VALIDATOR > seqW3("HelloWorld", Directionality::DIR_3_to_5);
    } catch (std::invalid_argument &e) {
        ASSERT_EQ(std::string(e.what()), "SimpleValidator's check of seq is failed on string: \"ACGT\"");
    }
}

TEST(TestSequenceWrapper, TestCopyConstructor) {
    const std::string s1 = "ACGT";
    const SequenceWrapper<DNA_VALIDATOR > SequenceWrapper1{s1, Directionality::DIR_5_to_3};
    ASSERT_EQ(s1, SequenceWrapper1.getSequence());

    SequenceWrapper<DNA_VALIDATOR > SequenceWrapper3{SequenceWrapper1};
    ASSERT_EQ(s1, SequenceWrapper3.getSequence());
}

TEST(TestSequenceWrapper, TestCopyOperator) {
    const std::string s1 = "ACGT";
    const std::string s2 = "AAAA";

    SequenceWrapper<DNA_VALIDATOR > SequenceWrapper1{s1, Directionality::DIR_5_to_3};
    SequenceWrapper<DNA_VALIDATOR > SequenceWrapper2{s2, Directionality::DIR_3_to_5};

    ASSERT_EQ(s1, SequenceWrapper1.getSequence());
    ASSERT_EQ(s2, SequenceWrapper2.getSequence());

    SequenceWrapper1 = SequenceWrapper2;
    ASSERT_EQ(s2, SequenceWrapper1.getSequence());
    ASSERT_EQ(Directionality::DIR_3_to_5, SequenceWrapper1.getDirectionality());
    SequenceWrapper2 = SequenceWrapper2;
    ASSERT_EQ(s2, SequenceWrapper2.getSequence());
}

TEST(TestSequenceWrapper, TestMoveConstructor) {
    std::string s1 = "ACGT";

    SequenceWrapper<DNA_VALIDATOR > SequenceWrapper1{s1, Directionality::DIR_5_to_3};
    ASSERT_EQ(s1, SequenceWrapper1.getSequence());

    const SequenceWrapper<DNA_VALIDATOR > SequenceWrapper3{std::move(SequenceWrapper1)};
    ASSERT_EQ(s1, SequenceWrapper3.getSequence());
    ASSERT_EQ(Directionality::DIR_5_to_3, SequenceWrapper3.getDirectionality());

    ASSERT_TRUE(SequenceWrapper1.getSequence().empty());
}

TEST(TestSequenceWrapper, TestMoveOperator) {
    const std::string s1 = "ACGT";
    const std::string s2 = "AAAA";

    SequenceWrapper<DNA_VALIDATOR > SequenceWrapper1{s1};
    SequenceWrapper<DNA_VALIDATOR > SequenceWrapper2{s2};

    ASSERT_EQ(s1, SequenceWrapper1.getSequence());
    ASSERT_EQ(s2, SequenceWrapper2.getSequence());

    SequenceWrapper1 = std::move(SequenceWrapper2);
    ASSERT_EQ(s2, SequenceWrapper1.getSequence());
    SequenceWrapper1 = std::move(SequenceWrapper1);
    ASSERT_EQ(s2, SequenceWrapper1.getSequence());
}

TEST(TestSequenceWrapper, TestSetDirectionality) {
    const std::string s1 = "ACGT";
    SequenceWrapper<DNA_VALIDATOR > SequenceWrapper1{s1, Directionality::DIR_5_to_3};
    ASSERT_EQ(s1, SequenceWrapper1.getSequence());
    ASSERT_EQ(Directionality::DIR_5_to_3, SequenceWrapper1.getDirectionality());

    SequenceWrapper1.setDirectionality(Directionality::DIR_3_to_5);
    ASSERT_EQ(s1, SequenceWrapper1.getSequence());
    ASSERT_EQ(Directionality::DIR_3_to_5, SequenceWrapper1.getDirectionality());

    SequenceWrapper1.setDirectionality(Directionality::DIR_3_to_5);
    ASSERT_EQ(s1, SequenceWrapper1.getSequence());
    ASSERT_EQ(Directionality::DIR_3_to_5, SequenceWrapper1.getDirectionality());
}

TEST(TestSequenceWrapper, TestReverseDirectionality) {
    const std::string s1 = "ACGT";
    SequenceWrapper<DNA_VALIDATOR > SequenceWrapper1{s1, Directionality::DIR_5_to_3};
    ASSERT_EQ(s1, SequenceWrapper1.getSequence());
    ASSERT_EQ(Directionality::DIR_5_to_3, SequenceWrapper1.getDirectionality());

    SequenceWrapper1.reverseDirectionality();
    ASSERT_EQ(s1, SequenceWrapper1.getSequence());
    ASSERT_EQ(Directionality::DIR_3_to_5, SequenceWrapper1.getDirectionality());

    SequenceWrapper1.reverseDirectionality();
    ASSERT_EQ(s1, SequenceWrapper1.getSequence());
    ASSERT_EQ(Directionality::DIR_5_to_3, SequenceWrapper1.getDirectionality());
}

TEST(TestSequenceWrapper, TestReverseSequenceWrapper) {
    const std::string s1 = "ACGT";
    const std::string s1_rev = "TGCA";
    SequenceWrapper<DNA_VALIDATOR > SequenceWrapper1{s1, Directionality::DIR_5_to_3};
    ASSERT_EQ(s1, SequenceWrapper1.getSequence());
    ASSERT_EQ(Directionality::DIR_5_to_3, SequenceWrapper1.getDirectionality());

    SequenceWrapper1.reverse();
    ASSERT_EQ(s1_rev, SequenceWrapper1.getSequence());
    ASSERT_EQ(Directionality::DIR_3_to_5, SequenceWrapper1.getDirectionality());

    SequenceWrapper1.reverse();
    ASSERT_EQ(s1, SequenceWrapper1.getSequence());
    ASSERT_EQ(Directionality::DIR_5_to_3, SequenceWrapper1.getDirectionality());
}

TEST(TestSequenceWrapper, TestLevenshteinDistance) {
    const std::string s1 = "taller";
    const std::string s2 = "falling";
    //dist = 4
    const SequenceWrapper<TrivialValidator> seq1(s1);
    const SequenceWrapper<TrivialValidator> seq2(s2);
    ASSERT_EQ(seq1.levenshteinDistance(seq2), 4);
    ASSERT_EQ(seq2.levenshteinDistance(seq1), 4);
    ASSERT_EQ(seq1.levenshteinDistance(seq1), 0);

    const SequenceWrapper<TrivialValidator> seq3("to maintain");
    const SequenceWrapper<TrivialValidator> seq4("mountain");

    // 3 additions or insertions : to mountain + 2 substitutions -- to maintain

    ASSERT_EQ(seq3.levenshteinDistance(seq4), 5);
    ASSERT_EQ(seq4.levenshteinDistance(seq3), 5);

    const SequenceWrapper<TrivialValidator> seq5("");
    ASSERT_EQ(seq5.levenshteinDistance(seq4), seq4.size());
    ASSERT_EQ(seq4.levenshteinDistance(seq5), seq4.size());
    ASSERT_EQ(seq5.levenshteinDistance(seq5), 0);

    const SequenceWrapper<TrivialValidator> seq6("ACGT-AAA");
    const SequenceWrapper<TrivialValidator> seq7("ACGTTACC");

    ASSERT_EQ(seq6.levenshteinDistance(seq7), 3);
}

TEST(TestSequenceWrapper, TestAlignment) {
    std::string s1 = "AGTACGCA";
    std::string s2 = "TATGC";

    SequenceWrapper<TrivialValidator> seq1(s1);
    SequenceWrapper<TrivialValidator> seq2(s2);

    auto res = seq1.align(seq2);
    ASSERT_EQ(res.first, seq1.getSequence());
    ASSERT_EQ(res.second, "--TATGC-");

    auto temp = seq2.align(seq1);

    s1 = "GCATGCG";
    s2 = "GATTACA";

    auto res1 = SequenceWrapper<TrivialValidator>(s1).align(SequenceWrapper<TrivialValidator>(s2));

    ASSERT_EQ(res1.first, "GCATG-CG");
    ASSERT_EQ(res1.second, "G-ATTACA");

    s1 = "AATGCA";
    s2 = "AAGC";

    auto res2 = SequenceWrapper<TrivialValidator>(s1).align(SequenceWrapper<TrivialValidator>(s2));
    ASSERT_EQ(res2.first, "AATGCA");
    ASSERT_EQ(res2.second, "AA-GC-");
}

TEST(TestSequenceWrapper, TestAlignmentReversed) {
    std::string s1, s2;
    s1 = "GCATGCG";
    // s2 = "GATTACA";
    // std::ranges::reverse(s2);
    s2 = "ACATTAG";

    auto res1 = SequenceWrapper<TrivialValidator>(s1).alignReversedDir(SequenceWrapper<TrivialValidator>(s2));

    ASSERT_EQ(res1.first, "GCATG-CG");
    ASSERT_EQ(res1.second, "G-ATTACA");


    s1 = "AGTACGCA";
    s2 = "TATGC";

    SequenceWrapper<TrivialValidator> seq1(s1);
    SequenceWrapper<TrivialValidator> seq2(s2, Directionality::DIR_5_to_3);

    auto res = seq1.alignReversedDir(seq2);
    ASSERT_EQ(res.first, seq1.getSequence());
    ASSERT_EQ(res.second, "--TATGC-");

    s1 = "GCATGCG";
    s2 = "GATTACA";

    auto res2 = SequenceWrapper<TrivialValidator>(s1).alignReversedDir(
        SequenceWrapper<TrivialValidator>(s2, Directionality::DIR_5_to_3));

    ASSERT_EQ(res2.first, "GCATG-CG");
    ASSERT_EQ(res2.second, "G-ATTACA");

    s1 = "AATGCA";
    s2 = "AAGC";

    auto res3 = SequenceWrapper<TrivialValidator>(s1).alignReversedDir(
        SequenceWrapper<TrivialValidator>(s2, Directionality::DIR_5_to_3));
    ASSERT_EQ(res3.first, "AATGCA");
    ASSERT_EQ(res3.second, "AA-GC-");
}

TEST(TestSequenceWrapper, TestBestAlignment) {
    std::string s1 = "AGTACGCA";
    std::string s2 = "TATGC";

    SequenceWrapper<TrivialValidator> seq1(s1);
    SequenceWrapper<TrivialValidator> seq2(s2);

    auto res = seq1.bestAlignment(seq2);
    ASSERT_EQ(res.first, seq1.getSequence());
    ASSERT_EQ(res.second, "--TATGC-");

    s1 = "AGTACGCA";
    s2 = "CGTAT";

    SequenceWrapper<TrivialValidator> seq3(s1);
    SequenceWrapper<TrivialValidator> seq4(s2, Directionality::DIR_5_to_3);

    auto resRev = seq3.bestAlignment(seq4);
    ASSERT_EQ(res.first, seq3.getSequence());
    ASSERT_EQ(res.second, "--TATGC-");
}


