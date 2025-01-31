// Copyright 2005, Google Inc.
// All rights reserved.

//
// Created by andru_kfgnofp on 12/14/2024.
//

#include <iostream>
#include "gtest/gtest.h"
#include "dna.h"

using namespace ::testing;

//todo rewrite tests to SequenceWrapper, not only DNA

TEST(TestDNA, TestTrueConstructors) {
    std::string s1 = "ACGT";
    std::string s2 = "AAAA";
    std::string s3 = "GTGT";

    DNA dna1{s1, Directionality::DIR_5_to_3};
    DNA dna2{Sequence(s2), Directionality::DIR_3_to_5};
    DNA dna3{"gtgt"};
    DNA dna4;

    ASSERT_EQ(s1, dna1.getSequence());
    ASSERT_EQ(s2, dna2.getSequence());
    ASSERT_EQ(s3, dna3.getSequence());
    ASSERT_EQ("", dna4.getSequence());

    ASSERT_EQ(Directionality::DIR_5_to_3, dna1.getDirectionality());
    ASSERT_EQ(Directionality::DIR_3_to_5, dna2.getDirectionality());
    ASSERT_EQ(ReplicationStatus::LEADING, dna1.getReplicationStatus());
    ASSERT_EQ(TranscriptionStatus::TEMPLATE, dna2.getTranscriptionStatus());
    ASSERT_EQ(Directionality::DIR_3_to_5, dna4.getDirectionality());
}

TEST(TestDNA, TestFalseConstructors) {
    std::string exceptionMessage1;

    const std::string s1 = "ACxT";

    try {
        DNA dna1{s1};
    } catch (std::invalid_argument &ex) {
        exceptionMessage1 = ex.what();
    }
    ASSERT_EQ(exceptionMessage1, "SimpleValidator's check of seq is failed on string: \"ACGT\"");
}

TEST(TestDNA, TestCopyConstructor) {
    std::string s1 = "ACGT";
    DNA dna1{s1, Directionality::DIR_5_to_3};
    ASSERT_EQ(s1, dna1.getSequence());

    DNA dna3{dna1};
    ASSERT_EQ(s1, dna3.getSequence());
}

TEST(TestDNA, TestCopyOperator) {
    std::string s1 = "ACGT";
    std::string s2 = "AAAA";

    DNA dna1{s1, Directionality::DIR_5_to_3};
    DNA dna2{s2, Directionality::DIR_3_to_5};

    ASSERT_EQ(s1, dna1.getSequence());
    ASSERT_EQ(s2, dna2.getSequence());

    dna1 = dna2;
    ASSERT_EQ(s2, dna1.getSequence());
    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());
    dna2 = dna2;
    ASSERT_EQ(s2, dna2.getSequence());
}

TEST(TestDNA, TestMoveConstructor) {
    std::string s1 = "ACGT";

    DNA dna1{s1, Directionality::DIR_5_to_3};
    ASSERT_EQ(s1, dna1.getSequence());

    DNA dna3{std::move(dna1)};
    ASSERT_EQ(s1, dna3.getSequence());
    ASSERT_EQ(Directionality::DIR_5_to_3, dna3.getDirectionality());

    ASSERT_TRUE(dna1.getSequence().empty());
}

TEST(TestDNA, TestMoveOperator) {
    std::string s1 = "ACGT";
    std::string s2 = "AAAA";

    DNA dna1{s1};
    DNA dna2{s2};

    ASSERT_EQ(s1, dna1.getSequence());
    ASSERT_EQ(s2, dna2.getSequence());

    dna1 = std::move(dna2);
    ASSERT_EQ(s2, dna1.getSequence());
    dna1 = std::move(dna1);
    ASSERT_EQ(s2, dna1.getSequence());
}

TEST(TestDNA, TestGettersSetters) {
    DNA dna1{"ACGT", Directionality::DIR_5_to_3};

    ASSERT_EQ(Directionality::DIR_5_to_3, dna1.getDirectionality());
    dna1.setDirectionality(Directionality::DIR_3_to_5);
    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());

    ASSERT_EQ(ReplicationStatus::LEADING, dna1.getReplicationStatus());
    dna1.setReplicationStatus(ReplicationStatus::LAGGING);
    ASSERT_EQ(ReplicationStatus::LAGGING, dna1.getReplicationStatus());

    ASSERT_EQ(TranscriptionStatus::TEMPLATE, dna1.getTranscriptionStatus());
    dna1.setTranscriptionStatus(TranscriptionStatus::CODING);
    ASSERT_EQ(TranscriptionStatus::CODING, dna1.getTranscriptionStatus());
}

TEST(TestDNA, TestReverseDNA) {
    std::string s1 = "ACGT";
    DNA dna1{s1, Directionality::DIR_5_to_3};
    ASSERT_EQ(s1, dna1.getSequence());
    ASSERT_EQ(Directionality::DIR_5_to_3, dna1.getDirectionality());

    dna1.reverse();

    ASSERT_EQ("TGCA", dna1.getSequence());
    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());
}

TEST(TestDNA, TestComplement) {
    std::string s1 = "CGTATGCTA";
    std::string s2 = "GCATACGAT";
    DNA dna1{s1, Directionality::DIR_3_to_5};

    ASSERT_EQ(s1, dna1.getSequence());

    dna1.complement();
    ASSERT_EQ(s2, dna1.getSequence());
    ASSERT_EQ(Directionality::DIR_5_to_3, dna1.getDirectionality());

    dna1.complement();
    ASSERT_EQ(s1, dna1.getSequence());
    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());
}

TEST(TestDNA, TestReverseComplement) {
    std::string s1 = "CGTATGCTA";
    std::string s2 = "TAGCATACG";
    DNA dna1{s1, Directionality::DIR_3_to_5};

    ASSERT_EQ(s1, dna1.getSequence());

    dna1.reverseComplement();
    ASSERT_EQ(s2, dna1.getSequence());
    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());

    dna1.reverseComplement();
    ASSERT_EQ(s1, dna1.getSequence());
    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());
}

TEST(TestDNA, IdempotenceOfComplements) {
    //complement + reverse complement + reverse = 2x complement + 2x reverse = doing nothing

    std::string s1 = "CGTATGCTA";

    DNA dna1{s1, Directionality::DIR_3_to_5};
    ASSERT_EQ(s1, dna1.getSequence());
    dna1.complement();
    dna1.reverseComplement();
    dna1.reverse();

    ASSERT_EQ(s1, dna1.getSequence());
    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());
}

TEST(TestDNA, TestReverseStatus) {
    DNA dna1{"ACGT", Directionality::DIR_5_to_3};
    ASSERT_EQ(Directionality::DIR_5_to_3, dna1.getDirectionality());
    dna1.reverseDirectionality();
    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());
    dna1.reverseDirectionality();
    ASSERT_EQ(Directionality::DIR_5_to_3, dna1.getDirectionality());

    ASSERT_EQ(ReplicationStatus::LEADING, dna1.getReplicationStatus());
    dna1.reverseReplicationStatus();
    ASSERT_EQ(ReplicationStatus::LAGGING, dna1.getReplicationStatus());
    dna1.reverseReplicationStatus();
    ASSERT_EQ(ReplicationStatus::LEADING, dna1.getReplicationStatus());

    ASSERT_EQ(TranscriptionStatus::TEMPLATE, dna1.getTranscriptionStatus());
    dna1.reverseTranscriptionStatus();
    ASSERT_EQ(TranscriptionStatus::CODING, dna1.getTranscriptionStatus());
    dna1.reverseTranscriptionStatus();
    ASSERT_EQ(TranscriptionStatus::TEMPLATE, dna1.getTranscriptionStatus());
}

TEST(TestDNA, TestTranscription) {
    std::string s1 = "ACACACTTTGGG";
    DNA dna1(s1, Directionality::DIR_3_to_5, ReplicationStatus::LEADING, TranscriptionStatus::CODING);
    DNA dna2{s1, Directionality::DIR_3_to_5, ReplicationStatus::LEADING, TranscriptionStatus::TEMPLATE};

    auto rna1 = dna1.transcribe();
    auto rna2 = dna2.transcribe();

    ASSERT_EQ(rna1.getSequence(), "ACACACUUUGGG");
    ASSERT_EQ(Directionality::DIR_3_to_5, rna1.getDirectionality());

    ASSERT_EQ(rna2.getSequence(), "UGUGUGAAACCC");
    ASSERT_EQ(Directionality::DIR_5_to_3, rna2.getDirectionality());
}

TEST(TestDNA, TestLevenshteinDistance) {
    std::string s1, s2;
    s1 = "ACGTACC";
    s2 = "ACGACCTT";

    ASSERT_EQ(3, DNA(s1).levenshteinDistance(DNA(s2)));
}

TEST(TestDNA, TestAlignment) {
    std::string s1 = "GCATGCG";
    std::string s2 = "GATTACA";

    auto res = DNA(s1).align(DNA(s2));
    ASSERT_EQ(res.first, "GCATG-CG");
    ASSERT_EQ(res.second, "G-ATTACA");

    std::ranges::reverse(s2);
    res = DNA(s1).align(DNA(s2, Directionality::DIR_5_to_3));
    ASSERT_EQ(res.first, "GCATG-CG");
    ASSERT_EQ(res.second, "G-ATTACA");
}

TEST(TestDNA, TestAlignmentReversed) {
    std::string s1 = "GCATGCG";
    std::string s2 = "ACATTAG";

    auto res = DNA(s1).alignReversedDir(DNA(s2));
    ASSERT_EQ(res.first, "GCATG-CG");
    ASSERT_EQ(res.second, "G-ATTACA");

    std::ranges::reverse(s2);
    res = DNA(s1).alignReversedDir(DNA(s2, Directionality::DIR_5_to_3));
    ASSERT_EQ(res.first, "GCATG-CG");
    ASSERT_EQ(res.second, "G-ATTACA");
}

TEST(TestDNA, TestAlignmentComplement) {
    std::string s1 = "GCATGCG";
    std::string s2 = "CTAATGT";

    auto res = DNA(s1).alignComplement(DNA(s2, Directionality::DIR_5_to_3));

    ASSERT_EQ(res.first, "GCATG-CG");
    ASSERT_EQ(res.second, "G-ATTACA");

    std::ranges::reverse(s2);
    res = DNA(s1).alignComplement(DNA(s2, Directionality::DIR_3_to_5));

    ASSERT_EQ(res.first, "GCATG-CG");
    ASSERT_EQ(res.second, "G-ATTACA");
}

TEST(TestDNA, TestAligmentReversedComplement) {
    std::string s1 = "GCATGCG";
    std::string s2 = "CTAATGT";

    auto res = DNA(s1).alignComplementReversedDir(DNA(s2));

    ASSERT_EQ(res.first, "GCATG-CG");
    ASSERT_EQ(res.second, "G-ATTACA");

    std::ranges::reverse(s2);
    res = DNA(s1).alignComplementReversedDir(DNA(s2, Directionality::DIR_5_to_3));

    ASSERT_EQ(res.first, "GCATG-CG");
    ASSERT_EQ(res.second, "G-ATTACA");
}

TEST(TestDNA, TestBestAligment) {
    std::string s1 = "GCATGCG";
    std::string s2 = "GATTACA";

    auto res = DNA(s1).bestAlignment(DNA(s2));
    ASSERT_EQ(res.first,  "GCATGCG");
    ASSERT_EQ(res.second, "ACATTAG");

    s1 = "AAAAACCCCGGGGA";
    s2 = "ATTTTTGGGGCCCC";

    res = DNA(s1).bestAlignment(DNA(s2));

    ASSERT_EQ(res.first,  "-AAAAACCCCGGGGA");
    ASSERT_EQ(res.second, "TAAAAACCCCGGGG-");
}
