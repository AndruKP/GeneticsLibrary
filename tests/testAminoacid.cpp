// Copyright 2005, Google Inc.
// All rights reserved.

//
// Created by andru_kfgnofp on 12/14/2024.
//

#include <fstream>
#include <iostream>
#include "gtest/gtest.h"
#include "Aminoacid.h"

using namespace ::testing;

TEST(TestAminoacid, TestConstructor) {
    Aminoacid am("UUU");
    ASSERT_EQ(am.getName(), "Phe");

    std::string ex;
    try {
        Aminoacid am2("UUUU");
    }
    catch(std::invalid_argument& e) {
        ex = e.what();
    }
    ASSERT_EQ(WRONG_CODON_ERROR_MESSAGE, ex);
}

TEST(TestAminoacid, TestInsertion) {
    Aminoacid am("UUU");
    std::ostringstream oss;
    oss << am << am << am;
    ASSERT_EQ(oss.str(), "PhePhePhe");
}
