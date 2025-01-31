// Copyright 2005, Google Inc.
// All rights reserved.

//
// Created by andru_kfgnofp on 12/14/2024.
//

#include <fstream>
#include <iostream>
#include "gtest/gtest.h"
#include "Protein.h"

using namespace ::testing;

TEST(TestProtein, TestConstructorAndIndices) {
    const std::vector<Aminoacid> chain = {Aminoacid("UUU"), Aminoacid("AAA")};

    const Protein protein1;
    const Protein protein2(chain);

    ASSERT_EQ(protein1.size(), 0);
    ASSERT_EQ(protein2.size(), 2);
    ASSERT_EQ(protein2[0].getName(), Aminoacid("UUU").getName());
    ASSERT_EQ(protein2[1].getName(), Aminoacid("AAA").getName());
}
TEST(TestProtein, TestAddAminoacid) {
    Protein protein;
    protein.addAminoacid("UUU");
    protein.addAminoacid(Aminoacid("AAA"));

    ASSERT_EQ(protein.size(), 2);
    ASSERT_EQ(protein[0].getName(), Aminoacid("UUU").getName());
    ASSERT_EQ(protein[1].getName(), Aminoacid("AAA").getName());
}


TEST(TestProtein, TestWrongIndices) {
    Protein protein;
    protein.addAminoacid("UUU");
    protein.addAminoacid("AAA");

    try {
        auto x = protein[2];
    } catch (std::exception &e) {
        ASSERT_EQ(std::string(e.what()), "Protein index is out of range: idx = 2 while size = 2");
    }

    try {
        auto x = protein[-1];
    } catch (std::exception &e) {
        ASSERT_EQ(std::string(e.what()), "Protein index is out of range: idx = 18446744073709551615 while size = 2");
    }
}

TEST(TestProtein, TestToString) {
    Protein protein;
    protein.addAminoacid("UUU");
    protein.addAminoacid("AAA");

    ASSERT_EQ(protein.toString(), "PheLys");

    Protein empty;
    ASSERT_EQ(empty.toString(), "");
}

