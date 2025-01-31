// Copyright 2005, Google Inc.
// All rights reserved.

//
// Created by andru_kfgnofp on 12/14/2024.
//

#include <iostream>
#include "gtest/gtest.h"
#include "rna.h"

using namespace ::testing;

TEST(TestRNA, TestConstructors) {
    const std::string s1 = "ACACACUUUGGG";
    const std::string s2 = "ACACACUUUGGG";

    const RNA rna1(s1, Directionality::DIR_3_to_5);
    const RNA rna2{s2, Directionality::DIR_3_to_5};

    ASSERT_EQ(rna1.getSequence(), s1);
    ASSERT_EQ(rna2.getSequence(), s2);
    ASSERT_EQ(rna1.getDirectionality(), Directionality::DIR_3_to_5);
    ASSERT_EQ(rna2.getDirectionality(), Directionality::DIR_3_to_5);

    try {
        RNA rna3{"ACfsgdjksdhjoi;njkx;dvsvbjkcsvsdbjKsvbjlkx", Directionality::DIR_5_to_3};
    }
    catch (std::invalid_argument &e) {
        ASSERT_EQ("SimpleValidator's check of seq is failed on string: \"ACGU\"", std::string(e.what()));
    }

    try {
        RNA rna4{Sequence("ACfsgdjksdhjoi;njkx;dvsvbjkcsvsdbjKsvbjlkx"), Directionality::DIR_5_to_3};
    }
    catch (std::invalid_argument &e) {
        ASSERT_EQ("SimpleValidator's check of seq is failed on string: \"ACGU\"", std::string(e.what()));
    }
}


TEST(TestRNA, TestReverseTranscription) {
    const std::string s1 = "ACACACUUUGGG";
    const std::string s2 = "UGUGUGAAACCC";
    const RNA rna1(s1, Directionality::DIR_3_to_5);
    const RNA rna2{Sequence(s2), Directionality::DIR_5_to_3};

    auto dna1 = rna1.reverseTranscribe(TranscriptionStatus::CODING);
    auto dna2 = rna2.reverseTranscribe(TranscriptionStatus::TEMPLATE);

    ASSERT_EQ(dna1.getSequence(), "ACACACTTTGGG");
    ASSERT_EQ(Directionality::DIR_3_to_5, dna1.getDirectionality());

    ASSERT_EQ(dna2.getSequence(), "ACACACTTTGGG");
    ASSERT_EQ(Directionality::DIR_3_to_5, dna2.getDirectionality());
}

TEST(TestRNA, TestTranslation) {
    const std::string s1 = "ACACACUUUGGG";
    std::string prot5to3 = "ThrHisPheGly";
    std::string prot3to5 = "GlyPheHisThr";

    const RNA rna1(s1, Directionality::DIR_5_to_3);
    const RNA rna2{s1, Directionality::DIR_3_to_5};

    const auto protein1 = rna1.translate();
    const auto protein2 = rna2.translate();

    ASSERT_EQ(prot5to3, protein1.toString());
    ASSERT_EQ(prot3to5, protein2.toString());

    const std::string s2 = "ACACACUUUGGGA";

    ASSERT_EQ(prot5to3, RNA(s2, Directionality::DIR_5_to_3).translate().toString());
    //ASSERT_EQ(prot3to5, RNA(s2, Directionality::DIR_3_to_5).translate());
    const std::string s3 = "ACACACUUUGGGAA";
    ASSERT_EQ(prot5to3, RNA(s3, Directionality::DIR_5_to_3).translate().toString());

    const std::string s4 = "GACACACUUUGGG";

    ASSERT_EQ(prot3to5, RNA(s4, Directionality::DIR_3_to_5).translate().toString());

    const std::string s5 = "GGACACACUUUGGG";

    ASSERT_EQ(prot3to5, RNA(s5, Directionality::DIR_3_to_5).translate().toString());
}
