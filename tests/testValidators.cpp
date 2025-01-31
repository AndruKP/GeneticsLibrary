// Copyright 2005, Google Inc.
// All rights reserved.

//
// Created by andru_kfgnofp on 12/14/2024.
//

#include <fstream>
#include <iostream>
#include "gtest/gtest.h"
#include "Validators.h"

using namespace ::testing;


TEST(TestValidators, TrivialValidator) {
    TrivialValidator::validate("test");
    TrivialValidator::validate("123");
    TrivialValidator::validate("AxU");
}

TEST(TestValidators, SimpleValidator) {
    SimpleValidator<CORRECT_DNA_BASES>::validate("ACGTGTGTGTGTACCC");
    SimpleValidator<CORRECT_RNA_BASES>::validate("UUUU");
    SimpleValidator<CORRECT_RNA_BASES>::validate("");

    try {
        SimpleValidator<CORRECT_DNA_BASES>::validate("UUUUUU");
    } catch (std::invalid_argument &e) {
        ASSERT_EQ(std::string(e.what()), "SimpleValidator's check of seq is failed on string: \"ACGT\"");
    }

    try {
        SimpleValidator<CORRECT_RNA_BASES>::validate("q");
    } catch (std::invalid_argument &e) {
        ASSERT_EQ(std::string(e.what()), "SimpleValidator's check of seq is failed on string: \"ACGU\"");
    }
}


